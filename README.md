# Luma OS

## Description

LumaOS is a x86 32-bit toy operating system, which I am developing to teach myself how operating systems work.
It is still in an very early development state, so don't try to use it.
LumaOS is primarily based on the Tutorials from James Molloy.

Features to implement (or already implemented):

- [x] Kernel (interfaced with the GRUB bootloader)
- [x] Global descriptor table (GDT)
- [x] ISRs for CPU interrupt handling
- [x] VGA graphics
- [x] Keyboard drivers
- [x] Filesystem (potentially ext2 (or not))
- [ ] Mouse drivers
- [x] Terminal (Shell)
- [x] Dynamic memory allocation
- [ ] Finalizing and adding GUI

## Usage

### Prerequisites

- qemu
- nasm
- make
- i386-elf-binutils
- i386-elf-gcc
- i386-elf-gdb
- xorriso
- grub-mkrescue

Example using Pamac (Arch Linux AUR helper):

```bash
pamac install qemu nasm make i386-elf-binutils i386-elf-gcc i386-elf-gdb xorriso grub-mkrescue
```

### Using

```bash
make run
```

### Cleaning the project

```bash
make clean
```

## Resources

- [Writing a Simple Operating System — from Scratch](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
- [OS Dev Wiki](https://wiki.osdev.org/Meaty_Skeleton)
- [JamesM's Kernel Development Tutorials](https://web.archive.org/web/20160412174753/http://www.jamesmolloy.co.uk/tutorial_html/index.html)
- [BrokenThorn Entertainment's Operating System Development Series](http://www.brokenthorn.com/Resources/OSDevIndex.html)
- [The Little Book About OS Development](https://littleosbook.github.io/)
- [C Memory Allocation Functions](http://www.sunshine2k.de/articles/coding/cmemalloc/cmemory.html)
