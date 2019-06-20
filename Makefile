make:
	nasm -f bin src/boot0.asm -o out/boot.out

bochs:
	bochs -f bochsrc.txt

qemu:
	qemu-system-i386 -fda out/boot.out

dump:
	gcc -Wall src/boot-dump.c -o out/test

log:
	./out/test > out/test.log

clean:
	rm out/*