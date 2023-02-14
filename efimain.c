
#include "efi.h"
#include "efilib.h"

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
 
	conOut->SetAttribute(conOut, EFI_WHITE);
	conOut->OutputString(conOut, u"Jumping to Loader ...\r\n");

    UINT8* loader = (UINT8*)OSBuffer;
    void (*LoaderFileBin)(BLOCKINFO*) = ((__attribute__((ms_abi)) void (*)(BLOCKINFO*) ) &loader[ENTRY_POINT]);
	
	LoaderFileBin(&bi);  // SUCCESS !!  Next video we add mmap. And then video after that, we add GDT / RSDP

	conOut->SetAttribute(conOut, EFI_GREEN);
	conOut->OutputString(conOut, u"Done\r\n");
	SystemTable->BootServices->WaitForEvent(1, &event, &index);
	
    return EFI_SUCCESS;
}

// Gonna call it here. Graphics works. Now we need to add to the loader.
// See you next video.
