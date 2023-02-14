gcc -Wall -Werror -m64 -std=c17 -mabi=ms -ffreestanding -c efimain.c -o efimain.o

gcc -Wall -Werror -m64 -std=c17 -mabi=ms efimain.o -shared -Wl,-dll -Wl,--subsystem,10 -Wl,--image-base -Wl,0x10000000 -e efi_main -o BOOTX64.EFI

gcc -Wall -Werror -m64 -mabi=ms -ffreestanding -Wl,--oformat=binary -e main -c os/loader.c -o os/loader.bin

del *.o

pause
