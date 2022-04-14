.set MAGIC,    0x1BADB002
.set FLAGS,    0
.set CHECKSUM, -(MAGIC + FLAGS)
.section .multiboot
.long MAGIC
.long FLAGS
.long CHECKSUM

stackBottom:
    .skip 1024

stackTop:
    .section .text
    .global _start
    .type _start, @function

_start:
	mov $stackTop, %esp
	call main
	cli

hltLoop:
	hlt
	jmp hltLoop

.size _start, . - _start