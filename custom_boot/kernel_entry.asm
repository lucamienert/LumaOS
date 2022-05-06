global _start

[bits 32]
_start:
    ; Calling the C Main function of the Kernel
    [extern main]
    call main
    jmp $