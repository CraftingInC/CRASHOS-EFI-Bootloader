#ifndef EFILIB_H
#define EFILIB_H

#include "efi.h"

#define NULL ((void*)0)

EFI_HANDLE          ImageHandle;
EFI_SYSTEM_TABLE*   SystemTable;

EFI_GRAPHICS_OUTPUT_PROTOCOL*       GraphicsAdapter;
EFI_GRAPHICS_OUTPUT_BLT_PIXEL       GraphicsColor;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*    conOut;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL*    Volume;
EFI_FILE_PROTOCOL*                  RootFileSystem = NULL;
EFI_FILE_PROTOCOL*                  FileTestHandle = NULL;
VOIDP                               OSBuffer;
unsigned int                        ENTRY_POINT;

typedef struct BLOCKINFO
{
	UINT64         BaseAddress;
	UINT64         BufferSize;
	UINT32         ScreenWidth;
	UINT32         ScreenHeight;
	UINT32         PixelsPerScanLine;
	UINT64         LoaderFileSize;
} __attribute__((__packed__)) BLOCKINFO;

struct BLOCKINFO bi;

void itoa(unsigned long int n, unsigned short int* buffer, int basenumber)
{
	unsigned long int hold;
	int i, j;
	hold = n;
	i = 0;
	do {
		hold = n % basenumber;
		buffer[i++] = (hold < 10) ? (hold + '0') : (hold + 'a' - 10);
	} while(n /= basenumber);
	
	buffer[i--] = 0;
	
	for(j = 0; j < i; j++, i--)
	{
		hold = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = hold;
	}
}

void InitVolume()
{
	EFI_LOADED_IMAGE_PROTOCOL* LoadedImageHandle = NULL;
	EFI_DEVICE_PATH_PROTOCOL*  DevicePath = NULL;
	if((SystemTable->BootServices->HandleProtocol(ImageHandle, &EFI_LOADED_IMAGE_PROTOCOL_GUID, (VOID**)&LoadedImageHandle)) == EFI_SUCCESS)
	{
		if((SystemTable->BootServices->HandleProtocol(LoadedImageHandle->DeviceHandle, &EFI_DEVICE_PATH_PROTOCOL_GUID, (VOID**)&DevicePath)) == EFI_SUCCESS)
		{
			if((SystemTable->BootServices->HandleProtocol(LoadedImageHandle->DeviceHandle, &EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (VOID**)&Volume)) == EFI_SUCCESS)
			{
				if((Volume->OpenVolume(Volume, &RootFileSystem)) != EFI_SUCCESS)
				{
				    conOut->OutputString(conOut, u"ERROR : Unable to open Volume.\r\n");
			    }
			}
		}
	}
}

void InitGraphics()
{
	if((SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 0, (void**)&GraphicsAdapter)) != EFI_SUCCESS)
	{
		conOut->OutputString(conOut, u"ERROR : Unable to enable Graphics.\r\n");
	}
	
	bi.BaseAddress           = GraphicsAdapter->Mode->FrameBufferBase;
	bi.BufferSize            = GraphicsAdapter->Mode->FrameBufferSize;
	bi.ScreenWidth           = GraphicsAdapter->Mode->Info->HorizontalResolution;
	bi.ScreenHeight          = GraphicsAdapter->Mode->Info->VerticalResolution;
	bi.PixelsPerScanLine     = GraphicsAdapter->Mode->Info->PixelsPerScanLine;
}

void CloseFile(EFI_FILE_PROTOCOL* FileHandle)
{
	if((FileHandle->Close(FileHandle)) != EFI_SUCCESS)
	{
		conOut->OutputString(conOut, u"ERROR : Unable to close file.\r\n");
	}
}

void ReadFile(CHAR16* FileName)  // NOTE : This auto-closes the file.
{
	if((RootFileSystem->Open(RootFileSystem, &FileTestHandle, FileName, EFI_FILE_MODE_READ, 0)) != EFI_SUCCESS)
	{
		conOut->OutputString(conOut, u"ERROR : Unable to read file.\r\n");
	} else {
		UINT64 fileSize = 0;
		FileTestHandle->SetPosition(FileTestHandle, 0xFFFFFFFFFFFFFFFFULL);
		FileTestHandle->GetPosition(FileTestHandle, &fileSize);
		FileTestHandle->SetPosition(FileTestHandle, 0);
		if((SystemTable->BootServices->AllocatePool(EfiLoaderData, fileSize, (void**)&OSBuffer)) == EFI_SUCCESS)
		{
			FileTestHandle->SetPosition(FileTestHandle, 0);
			if((FileTestHandle->Read(FileTestHandle, &fileSize, OSBuffer)) != EFI_SUCCESS)
			{
				conOut->OutputString(conOut, u"ERROR : Unable to read file contents.\r\n");
			}
			
			UINT8* test = (UINT8*)OSBuffer;
			UINT8  p1, p2, p3, p4;
			p1 = *test;
			test += 1;
			p2 = *test;
			test += 1;
			p3 = *test;
			test += 1;
			p4 = *test;
			if(p1 == 100 && p2 == 134)
			{
				conOut->OutputString(conOut, u"Found the 8664 ENTRY_POINT.\r\n");
				test += 37;
				p1 = *test;
				test += 1;
				p2 = *test;
				test += 1;
				p3 = *test;
				test += 1;
				p4 = *test;
				ENTRY_POINT = (p4 << 24) | (p3 << 16) | (p2 << 8) | p1;
			} else {
				ENTRY_POINT = 0;
				conOut->OutputString(conOut, u"ERROR : Unable to find the 8664 ENTRY_POINT.\r\n");
			}
			CloseFile(FileTestHandle);
			bi.LoaderFileSize = fileSize;
		} else {
			conOut->OutputString(conOut, u"ERROR : Unable to Allocate Pool.\r\n");
		}
	}
}

/*
#define ORANGE 0xffffa500

void SetGraphicsColor(UINT32 color)
{
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL tempColor;
	tempColor.Reserved   = color >> 24;
	tempColor.Red        = color >> 16;
	tempColor.Green      = color >> 8;
	tempColor.Blue       = color;
	GraphicsColor = tempColor;
}

// NOTE : Call SetGraphicsColor Prior to this function.
void tempGraphicsTest()
{
	UINT32 xPos, yPos, w, h, x, y, WIDTH, HEIGHT;
	xPos = 10;
	yPos = 10;
	w = 100;
	h = 100;
	
	UINT32 ByteOffset = 4;
	x       = 0;
	y       = yPos;
	WIDTH   = (xPos + w) + ByteOffset;
	HEIGHT  = yPos + h;
	for(y = yPos; y <= HEIGHT; y++)
	{
		for(x = xPos * ByteOffset; x <= WIDTH; x += ByteOffset)
		{
			*(UINT32*) (x + (y * bi.PixelsPerScanLine * ByteOffset) + bi.BaseAddress) = *(UINT32*)&GraphicsColor;
		}
	}
}
*/

#endif  // EFILIB_H