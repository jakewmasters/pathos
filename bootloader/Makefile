# Bootloader Makefile

AS = nasm

# quick macro to build and run really fast
all:
	make build && make floppy && make write && make qemu

# build object files for each asm source
build: 
	$(AS) -f bin bootloader.s -o bootloader

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
	rm bootloader disk.img sample

# gdb commands
# set architecture i8086
# target remote localhost:26000
# layout asm
# layout regs
# b *0x500
# c
# q
