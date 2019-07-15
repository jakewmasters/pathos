# PathOS
Performant and Theoretically Helpful Operating System  

Currently a small, bootable microkernel. 

While the development of this project has been heavily inspired by a plethora of sources, all code in this repository is my own. 

## Organization

All code related to the boot process is found in the `bootloader/` directory.   

The bootloader ultimately calls `kmain()`.
This function is found in `kernel.c`, which is found in the `src` directory. 

All kernel modules are currently found within the `src` directory. 
These include:  
- A simple framebuffer driver. 
- A time library. 
- A minimal C standard library. 
- A module for reading and writing to I/O ports. 

## Build
Build image:
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

On my machine, `qemu` is a little bit faster to get up and going with, but `bochs` has a lot of useful debug functionality.  
Pick your poison.

## Design Decisions

### GDT
For sake of simplicity, I am using the most minimal Global Descriptor Table possible, described by Intel as the *basic flat model*. 

My GDT consists of three segment descriptors: 
- The null segment descriptor, required by default. 
- The code segment descriptor, which denotes the region containing all executable instructions. 
- The data segment descriptor, which denotes the region containing all non-executable data. 

### Timing
I decided to use the TSC (Time Stamp Counter) for sake of **simplicity** and **efficiency**. 
While it relates more to clock rate than actual time elapsed, the TSC is easily accessed via the `RDTSC` x86 instruction. 
A [benchmark by Red Hat](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_MRG/2/html/Realtime_Reference_Guide/chap-Timestamping.html) showed that TSC is 20 times more efficient than HPET.  

The tradeoff I'm making here is **portability**. Not all processors have a TSC register. 
With this in mind, PathOS currently only ports to Intel processors starting at the Pentium model (1993 and on).  

I also have begun offering limited support for the Real-Time Clock (RTC), located on the CMOS chip. 
While not desirable for high-resolution timing, it definitely offers a lot of general utility. 

In the future I would like to add support for HPET (High Precision Event Timer). 
HPET is more scalable and synchronizes well across multiple processors. 
