# PathOS
Performant and Theoretically Helpful Operating System  

Currently a small, bootable microkernel. 

## Organization

Currently using GRUB as a drop-in bootloader for now. See `iso/boot/`. 

GRUB then starts executing the x86 code found in `loader.s`, which finally transfers control to `kernel.c`. 

## Build
Assemble:
```
$ make
```
Run on bochs:
```
$ make bochs
```
Run on qemu:
```
$ make qemu
```

On my machine, `qemu` is a little bit faster to get up and going with, but `bochs` has a lot of fun debug stuff.  
Pick your poison.