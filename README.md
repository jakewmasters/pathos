# PathOS
Performant and Theoretically Helpful Operating System  

Currently able to set `eax` to `0xDEADBEEF` from a C program.  

Using GRUB as a drop-in bootloader for now. 

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