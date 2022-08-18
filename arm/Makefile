ASM_FILES = $(wildcard boot/*.s)
C_SOURCES = $(wildcard kernel/*.c drivers/*.c lib/*.c)

OBJ_FILES = ${C_SOURCES:.c=.o}
OBJ_FILES += ${ASM_FILES:.s=.o}

C_FLAGS = -Iinclude -Wall -Wextra -nostdlib -nostartfiles -ffreestanding -std=gnu99

%.o: %.s
	arm-elf-as $< -o $@

%.o: %.c
	arm-elf-gcc ${C_FLAGS} -c $< -o $@

LumaOSARM.img: ${OBJ_FILES}
	arm-elf-ld -T link.ld -o $@ $<

qemu: LumaOSARM.img
	qemu-system-arm -m 128 -kernel $<

clean:
	rm boot/*.o
	rm drivers/*.o
	rm kernel/*.o
	rm lib/*.o