
#include "efi.h"
#include "efilib.h"

//#include <string.h>     // strcmp()   For some reason, strcmp() will not work. Had to write my own.


unsigned long long strlen(const char* str)
{
	const char* strCount = str;

	while (*strCount++);
	return strCount - str - 1;
}

int m_strcmp(char* a, char* b)
{
	int length = strlen(a);
	for(unsigned int i = 0; i < length; i++)
	{
		if(a[i] > b[i]){return  1;}
		if(a[i] < b[i]){return -1;}
	}
	return 0;
}



typedef long long INTN;

UINT64 CompareGuid(EFI_GUID* guid1, EFI_GUID* guid2)
{
	// I originally got this from the GNU-EFI
	UINT32 *g1, *g2;
	UINT64 r = 0;
	g1 = (UINT32*) guid1;
	g2 = (UINT32*) guid2;
	r  = g1[0] - g2[0];
	r |= g1[1] - g2[1];
	r |= g1[2] - g2[2];
	r |= g1[3] - g2[3];

	return r;
}

EFI_STATUS efi_main(EFI_HANDLE IH, EFI_SYSTEM_TABLE *ST)
{
	ImageHandle = IH;
	SystemTable = ST;

	UINTN index;
	EFI_EVENT event = SystemTable->ConIn->WaitForKey;
	conOut = SystemTable->ConOut;
	conOut->Reset(conOut, 1);

    InitGraphics();

	InitVolume();

 	ReadFile(u"EFI\\BOOT\\loader.bin");

	// The RSDP I'll add in next video.  Screw it, I'll see if I can add it now. It technically should work without the GDT since we are still in EFI land. The GDT is definately a next video thing.
	// As you can see, it's quite extensive and we can access ANY hardware once this is setup and sent to our loader.
	
	conOut->OutputString(conOut, u"Grabbing RSDP ...\r\n");

	EFI_CONFIGURATION_TABLE* configTable = SystemTable->ConfigurationTable;
	unsigned long long* tempRSDP = NULL;
	for(UINTN index = 0; index < SystemTable->NumberOfTableEntries; index++)
	{
		if((CompareGuid(&configTable[index].VendorGuid, &EFI_ACPI_20_TABLE_GUID)) && (m_strcmp((char*)"RSD PTR ", (char*)configTable->VendorTable) == 0))
		{
			conOut->SetAttribute(conOut, EFI_RED);
			conOut->OutputString(conOut, u"Found EFI_ACPI_20_TABLE_GUID --->  ");
			conOut->SetAttribute(conOut, EFI_WHITE);
			conOut->OutputString(conOut, u"Found RSD PTR -->  ");
			tempRSDP = (void*)configTable->VendorTable;
			INTN r = CompareGuid(&configTable[index].VendorGuid, &EFI_ACPI_20_TABLE_GUID);
			UINT16 GOPINFO[12];
			conOut->SetAttribute(conOut, EFI_CYAN);
			conOut->OutputString(conOut, u"RESULT : ");
			conOut->SetAttribute(conOut, EFI_YELLOW);
			itoa(r, GOPINFO, 10);
			conOut->OutputString(conOut, GOPINFO);
			conOut->OutputString(conOut, u"\r\n");
		}
		configTable++;
	}

    conOut->SetAttribute(conOut, EFI_BROWN);
    conOut->OutputString(conOut, u"\r\nNOTE : Only the last RSDP is saved. It MIGHT be a problem.\r\n\r\n");
	conOut->SetAttribute(conOut, EFI_GREEN);
    conOut->OutputString(conOut, u"Grabbing MMAP ...\r\n");

// NOTE : Do NOT use any conOut from this point on. It messes up the MMap.
    UINTN                   MemoryMapSize = 0;
	EFI_MEMORY_DESCRIPTOR*  MemoryMap = NULL;
	UINTN                   MapKey;
	UINTN                   DescriptorSize;
	UINT32                  DescriptorVersion;
	
	if((SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion)) != EFI_SUCCESS)
	{
		// Technically this should fail, because you have to call this twice for it to fill in all the data required.
		MemoryMapSize += 2 * DescriptorSize;  // Trick to expand it.
		SystemTable->BootServices->AllocatePool(AllocateAddress, MemoryMapSize, (void**)&MemoryMap);  // EFI's Malloc
		if((SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion)) != EFI_SUCCESS)
		{
			conOut->OutputString(conOut, u"ERROR : EFI_MEMORY_DESCRIPTOR Failed.\r\n");
		}
	}
	
	// Fill in the BLOCKINFO*
	bi.MMap                  = MemoryMap;
	bi.MMapSize              = MemoryMapSize;
	bi.MMapDescriptorSize    = DescriptorSize;
	bi.rsdp                  = tempRSDP;
	
//	conOut->SetAttribute(conOut, EFI_WHITE);
//	conOut->OutputString(conOut, u"Jumping to Loader ...\r\n");

    UINT8* loader = (UINT8*)OSBuffer;
    void (*LoaderFileBin)(BLOCKINFO*) = ((__attribute__((ms_abi)) void (*)(BLOCKINFO*) ) &loader[ENTRY_POINT]);
	
	// Exit EFI here.
	SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);
	
	// If that works, we officially are on our own with the loader.
	
	LoaderFileBin(&bi);

	conOut->SetAttribute(conOut, EFI_RED);
	conOut->OutputString(conOut, u"If you see this, then something went wrong.\r\n");
	SystemTable->BootServices->WaitForEvent(1, &event, &index);
	
    return EFI_SUCCESS;
}

