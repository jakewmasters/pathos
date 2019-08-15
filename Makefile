# PathOS Makefile

AS = nasm
CC = i686-elf-gcc
LD = ld

CFLAGS = -m32 -ffreestanding -fno-pie -c
OBJECTS = kernel_entry.o kernel.o framebuffer.o io.o pathstd.o time.o idt.o isr.o interrupt.o keyboard.o shell.o vm.o

# macro to build final image
build:
	make -B bootloader && make asm && make compile && make link && make final

# build bootloader separate, since it's a bin not an elf
bootloader:
	$(AS) bootloader/boot32.s -f bin -o boot.bin

# build all assembly parts as elfs
asm:
	$(AS) bootloader/kernel_entry.s -f elf -o kernel_entry.o
	$(AS) src/kernel/io.s -f elf -o io.o
	$(AS) src/kernel/interrupt.s -f elf -o interrupt.o

# compile all c files into objects
compile:
	$(CC) $(CFLAGS) src/kernel/kernel.c -o kernel.o
	$(CC) $(CFLAGS) src/kernel/framebuffer.c -o framebuffer.o
	$(CC) $(CFLAGS) src/kernel/time.c -o time.o
	$(CC) $(CFLAGS) src/kernel/idt.c -o idt.o
	$(CC) $(CFLAGS) src/kernel/isr.c -o isr.o
	$(CC) $(CFLAGS) src/kernel/keyboard.c -o keyboard.o
	$(CC) $(CFLAGS) src/kernel/vm.c -o vm.o
	$(CC) $(CFLAGS) src/lib/pathstd.c -o pathstd.o
	$(CC) $(CFLAGS) src/lib/shell.c -o shell.o

# link everything into kernel.bin
link:
	$(LD) -o kernel.bin -melf_i386 -e kmain -Ttext 0x1000 $(OBJECTS) --oformat binary

# concatenate binaries into final image
final:
	cat boot.bin kernel.bin > os-image

# run on qemu
qemu:
	qemu-system-i386 -fda os-image

# run on qemu with debug session
debug:
	qemu-system-i386 -fda os-image -S -gdb tcp::26000

# run on bochs
bochs:
	bochs

# produce an ISO for vbox
# iso:
	# genisoimage -no-emul-boot -boot-load-size 32 -o pathos.iso -V PathOS -b boot.bin iso/
	# dd if=os-image of=pathos.img bs=512 count=32

# clean up intermediate files
clean:
	rm *.bin *.o os-image