ASM_FILES = $(wildcard boot/*.s include/asm/*.s)
C_SOURCES = $(wildcard kernel/*.c kernel/memory/*.c kernel/cpu/*.c drivers/*.c cpu/*.c libc/*c fs/*.c gui/*.c)
HEADERS = $(wildcard include/*.h include/kernel/*.h include/kernel/cpu/*.h include/kernel/memory/*.h include/drivers/*.h include/asm/*.h include/gui/*.h include/fs/*h include/system/*.h)

C_OBJ_FILES = ${C_SOURCES:.c=.o}
ASM_OBJ_FILES = ${ASM_FILES:.s=.o}

C_FLAGS = -m32 -ffreestanding -Wall -I./include -nostdlib

OUTPUT_ISO = LumaOS.iso

all: multiboot buildgrub run

%.o: ${ASM_FILES}
	@echo "[Makefile]: Converting Assembly Files"
	as --32 $< -o $@

%.o: ${C_SOURCES} ${HEADERS}
	@echo "[Makefile]: Converting C Files"
	x86_64-elf-gcc -g ${C_FLAGS} -c $< -o $@

LumaOS.bin: ${ASM_OBJ_FILES} ${C_OBJ_FILES}
	@echo "[Makefile]: Linking the object Files"
	x86_64-elf-ld -m elf_i386 -T linker.ld -o $@ $^ -nostdlib

multiboot: LumaOS.bin
	@echo "[Makefile]: Checking if Binary iss x86 Multiboot...""
	grub-file --is-x86-multiboot $<

buildgrub: LumaOS.bin
	@echo "[Makefile]: Copying the everything to ./bin Folder"
	mkdir -p bin/boot/grub
	cp $< bin/boot/$<
	cp grub.cfg bin/boot/grub/grub.cfg
	@echo "[Makefile]: Creating ISO"
	grub-mkrescue -o ${OUTPUT_ISO} bin

run:
	@echo "[Makefile]: Running the ISO"
	qemu-system-i386 -cdrom bin/${OUTPUT_ISO}

clean:
	rm bin/*.bin *.o *.dis *.elf
	rm kernel/*.o
	rm boot/*.o
	rm drivers/*.o
	rm fs/*.o
	rm gui/*.o
	rm libc/*.o
