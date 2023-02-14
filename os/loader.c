
#include <stdint.h>

#define ORANGE 0xffffa500
#define MAUVE  0xffaa55aa

typedef struct EFI_MEMORY_DESCRIPTOR
{
	uint32_t         Type;
	uint64_t         PhysicalStart;
	uint64_t         VirtualStart;
	uint64_t         NumberOfPages;
	uint64_t         Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef struct GraphicsPixelColor
{
	uint8_t          Blue;
	uint8_t          Green;
	uint8_t          Red;
	uint8_t          Alpha;
} GraphicsPixelColor;

typedef struct BLOCKINFO
{
	uint64_t                   BaseAddress;
	uint64_t                   BufferSize;
	uint32_t                   ScreenWidth;
	uint32_t                   ScreenHeight;
	uint32_t                   PixelsPerScanLine;
	uint64_t                   LoaderFileSize;
	EFI_MEMORY_DESCRIPTOR*     MMap;
	uint64_t                   MMapSize;
	uint64_t                   MMapDescriptorSize;
	unsigned long long*        rsdp;
} __attribute__((__packed__)) BLOCKINFO;

BLOCKINFO* biStruct __attribute__ ((section(".text")));
void CreateFilledBox(uint32_t xPos, uint32_t yPos, uint32_t w, uint32_t h, uint32_t c);

void main(BLOCKINFO* bi)
{
	biStruct = bi;
	biStruct->BaseAddress = bi->BaseAddress;
	CreateFilledBox(10, 10, 100, 100, MAUVE);
	
	while(1){__asm__("hlt");}
}

void CreateFilledBox(uint32_t xPos, uint32_t yPos, uint32_t w, uint32_t h, uint32_t c)
{
	uint32_t x, y, WIDTH, HEIGHT;
	x       = 0;
	y       = yPos;
	WIDTH   = xPos + w;
	HEIGHT  = yPos + h;
	for(y = yPos; y <= HEIGHT; y++)
	{
		for(x = xPos; x <= WIDTH; x++)
		{
			*(x + (y * biStruct->PixelsPerScanLine) + (uint32_t*)(biStruct->BaseAddress)) = c;
		}
	}
}
