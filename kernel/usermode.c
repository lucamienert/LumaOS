#include "../include/kernel/usermode.h"

void switch_to_user_mode()
{
    __asm__ volatile(" \
        cli; \
        mov $0x23, %ax; \
        mov %ax, %ds; \
        mov %ax, %es; \
        mov %ax, %fs; \
        mov %ax, %gs; \
        \
        mov %esp, %eax; \
        pushl $0x23; \
        pushf; \
        pushl $0x1B; \
        push $1f; \
        iret; \
        1: \
    ");
}