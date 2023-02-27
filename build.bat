@echo off
rem Bat file for windows
@echo on

gcc -Wall -Werror -m64 -std=c17 -O2 -ffreestanding -c efiboot/efimain.c -o efimain.o

gcc -Wall -Werror -m64 -std=c17 -O2 efimain.o -shared -Wl,-dll -Wl,--subsystem,10 -Wl,--image-base -Wl,0x10000000 -e efi_main -o BOOTX64.EFI

gcc -Wall -Werror -m64 -std=c17 -O0 -mabi=ms -ffreestanding -Wl,--oformat=binary -e main -c loader.c -o loader.bin

del *.o

pause
