make:
	nasm -f elf32 src/loader.s -o out/loader.o && ld -T src/link.ld -melf_i386 out/loader.o -o iso/boot/kernel.elf

iso:
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso

bochs:
	bochs -f bochsrc.txt -q

qemu:
	qemu-system-i386 -fda out/boot.out

dump:
	gcc -Wall src/boot-dump.c -o out/test

log:
	./out/test > out/test.log

clean:
	rm out/* *.iso bochsout.txt
