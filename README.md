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

## Current State
This project is admittedly all over the place.  

I am currently able to boot my C kernel using GRUB, 
however I am also working on building my own bootloader in parallel. 

Everything related to my own custom bootloader is located in the top-level `bootloader` directory of this project.  

My own personal notes, remarks, and various scribblings are located in the top-level `docs/` directory.  

My GRUB-bootable microkernel, libraries, and device drivers are all located in the top-level `src/` directory.  

Various GRUB-related build stuff is located in the top-level `iso/` directory.  

## Design Decisions

### Timing
I decided to use the TSC (Time Stamp Counter) for sake of simplicity and efficiency. 
While it relates more to clock rate than actual time elapsed, the TSC is easily accessed via the `RDTSC` x86 instruction. 
A [benchmark by Red Hat](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_MRG/2/html/Realtime_Reference_Guide/chap-Timestamping.html) showed that TSC is 20 times more efficient than HPET. 

In the future I would like to add support for HPET (High Precision Event Timer). 
HPET is more scalable and synchronizes well across multiple processors. 
