# Bootloader Makefile

AS = nasm
CC = i686-elf-gcc
LD = ld

# quick macro to build and run really fast
all:
	make build && make floppy && make write

# trying to do everything at once
test:
	nasm boot32.s -f bin -o boot.bin
	gcc -m32 -ffreestanding -fno-pie -c kernel.c -o kernel.o
	ld -o kernel.bin -melf_i386 -Ttext 0x1000 kernel.o --oformat binary
	cat boot.bin kernel.bin > os-image
	qemu-system-i386 -fda os-image -gdb tcp::26000 -S
	# bochs

# build object files for each asm source
build: 
	$(AS) -f bin boot32.s -o bootloader
	#$(CC) -ffreestanding -c kernel.c -o kernel.o
	#$(LD) -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary

# creates a blank floppy disk with 2880 512-byte sectors
floppy:
	dd if=/dev/zero of=disk.img bs=512 count=2880

# replaces first, writes MBR to first sector plus 5 more sectors
write:
	dd conv=notrunc if=bootloader of=disk.img bs=512 count=6 seek=0

# writes the MBR to the first sector of the floppy disk
first:
	dd conv=notrunc if=bootloader of=disk.img bs=512 count=1 seek=0

# writes the next stage to the second sector of the floppy disk
second:
	dd if=sample of=disk.img bs=512 count=1 seek=1

# run qemu
qemu:
	qemu-system-i386 -machine q35 -fda disk.img

# run qemu with remote gdb session enabled
qemu-debug:
	qemu-system-i386 -machine q35 -fda disk.img -gdb tcp::26000 -S

# run bochs
bochs:
	bochs

# clean up build files
clean:
	rm bootloader sample os-image bochsout.txt *.img *.o *.bin

# gdb commands
# set architecture i8086
# target remote localhost:26000
# layout asm
# layout regs
# b *0x500
# c
# q
