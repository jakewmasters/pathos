make:
	nasm -f bin src/old-boot/boot0.asm -o out/boot.out

bochs:
	bochs -f bochsrc.txt -q

qemu:
	qemu-system-i386 -fda out/boot.out

dump:
	gcc -Wall src/old-boot/boot-dump.c -o out/test

log:
	./out/test > out/test.log

iso:
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso

clean:
	rm out/*