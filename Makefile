make:
	cd src/ && make clean && make && cd .. && make -B iso && echo "Success! Now just run with Bochs (make bochs)"

iso:
	cp src/kernel.elf iso/boot/kernel.elf
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
	rm *.iso bochsout.txt
