# PathOS Makefile

AS = nasm
CC = i686-elf-gcc
LD = ld

CFLAGS = -m32 -ffreestanding -fno-pie -c
OBJECTS = kernel_entry.o kernel.o framebuffer.o io.o pathstd.o

# macro to build final image
build:
	make bootloader && make asm && make compile && make link && make final

# build bootloader separate, since it's a bin not an elf
bootloader:
	$(AS) boot32.s -f bin -o boot.bin

# build all assembly parts as elfs
asm:
	$(AS) kernel_entry.s -f elf -o kernel_entry.o
	$(AS) io.s -f elf -o io.o

# compile all c files into objects
compile:
	$(CC) $(CFLAGS) kernel.c -o kernel.o
	$(CC) $(CFLAGS) framebuffer.c -o framebuffer.o
	$(CC) $(CFLAGS) pathstd.c -o pathstd.o

# link everything into kernel.bin
link:
	$(LD) -o kernel.bin -melf_i386 -e kmain -Ttext 0x1000 $(OBJECTS) --oformat binary

# concatenate binaries into final image
final:
	cat boot.bin kernel.bin > os-image

# run on qemu
qemu:
	qemu-system-i386 -fda os-image

# run on bochs
bochs:
	bochs

# clean up intermediate files
clean:
	rm *.bin *.o