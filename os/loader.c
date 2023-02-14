
#include <stdint.h>

#define ORANGE 0xffffa500
#define MAUVE  0xffaa55aa

typedef struct GraphicsPixelColor
{
	uint8_t          Blue;
	uint8_t          Green;
	uint8_t          Red;
	uint8_t          Alpha;
} GraphicsPixelColor;

typedef struct BLOCKINFO
{
	uint64_t         BaseAddress;
	uint64_t         BufferSize;
	uint32_t         ScreenWidth;
	uint32_t         ScreenHeight;
	uint32_t         PixelsPerScanLine;
	uint64_t         LoaderFileSize;
} __attribute__((__packed__)) BLOCKINFO;

// Do to how the file is designed, we need to insert WHERE the BLOCKINFO can be accessed.
BLOCKINFO* biStruct __attribute__ ((section(".text")));
void CreateFilledBox(uint32_t xPos, uint32_t yPos, uint32_t w, uint32_t h, uint32_t c);

void main(BLOCKINFO* bi)
{
	biStruct = bi;
	biStruct->BaseAddress = bi->BaseAddress;  // This is to make sure we have the correct Address. Kinda overkill, but needed.
	CreateFilledBox(10, 10, 100, 100, MAUVE);
	
	while(1){__asm__("hlt");}   // CPU instruction in Assembly to halt the CPU.
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

// Now this is ready once we load it into memory to run. Cross fingers it works once we do get to this point.