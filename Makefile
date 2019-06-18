make:
	nasm -f bin src/boot.S -o boot.out

bochs:
	bochs -f bochsrc.txt

qemu:
	qemu-system-i386 -fda boot.out

clean:
	rm *.out