# PathOS Makefile

AS = nasm
CC = i686-elf-gcc
LD = ld

# quick macro to build final image
all:
	make build && make final

# assemble, compile, and link all binaries
build:
	$(AS) boot32.s -f bin -o boot.bin
	$(AS) kernel_entry.s -f elf -o kernel_entry.o
	$(CC) -m32 -ffreestanding -fno-pie -c kernel.c -o kernel.o
	$(LD) -o kernel.bin -melf_i386 -e kmain -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary

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