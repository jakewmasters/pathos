OBJECTS = loader.o kernel.o framebuffer.o io.o pathstd.o time.o

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -fomit-frame-pointer -Wno-unused-function -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf
AS_HEADERS = constants.inc

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	./c_to_nasm.sh $(AS_HEADERS)
	$(AS) $(ASFLAGS) $<

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

clean:
	rm -rf *.o *.elf *.inc