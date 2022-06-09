export

ASM_FILES = $(wildcard boot/*.s include/asm/*.s kernel/asm/*.s)
C_SOURCES = $(wildcard kernel/*.c kernel/memory/*.c kernel/cpu/*.c drivers/*.c cpu/*.c libc/*c libc/ds/*.c fs/*.c gui/*.c gui/widgets/*.c)
HEADERS = $(wildcard include/*.h include/kernel/*.h include/kernel/cpu/*.h include/kernel/memory/*.h include/kernel/net/*.h include/kernel/net/socket/*.h include/drivers/*.h include/asm/*.h include/gui/*.h include/gui/widgets/*.h include/fs/*.h include/system/*.h include/ds/*.h)

C_OBJ_FILES = ${C_SOURCES:.c=.o}
ASM_OBJ_FILES = ${ASM_FILES:.s=.o}

OBJ_FILES = ${C_SOURCES:.c=.o}
OBJ_FILES += ${ASM_FILES:.s=.o}

C_FLAGS = -m32 -ffreestanding -Wall -I/include -nostdlib

OUTPUT_ISO = LumaOS.iso

all: multiboot buildgrub run

%.o: %.s
	$(info [asm] $@)
	as --32 $< -o $@

%.o: %.c ${HEADERS}
	$(info [c] $@)
	x86_64-elf-gcc -g ${C_FLAGS} -c $< -o $@

LumaOS.bin: ${ASM_OBJ_FILES} ${C_OBJ_FILES}
	x86_64-elf-ld -m elf_i386 -T linker.ld -o $@ $^ -nostdlib

multiboot: LumaOS.bin
	grub-file --is-x86-multiboot $<

buildgrub: LumaOS.bin
	mkdir -p bin/boot/grub
	cp $< bin/boot/$<
	cp grub.cfg bin/boot/grub/grub.cfg
	grub-mkrescue -o ${OUTPUT_ISO} bin

run:
	@echo "[Makefile]: Running the ISO"
	qemu-system-i386 -cdrom bin/${OUTPUT_ISO}

${OUTPUT_ISO}:
	$(info [all] writing $@)
	@grub-mkrescue -o ${OUTPUT_ISO} bin

qemu: ${OUTPUT_ISO}
	qemu-system-i386 -cdrom ${OUTPUT_ISO} -monitor stdio -s -no-reboot

clean:
	rm bin/*.bin *.o *.dis *.elf
	rm kernel/*.o
	rm boot/*.o
	rm drivers/*.o
	rm fs/*.o
	rm gui/*.o
	rm libc/*.o
