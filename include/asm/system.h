#ifndef LUMAOS_SYSTEM_H_
#define LUMAOS_SYSTEM_H_

#pragma once

#define CLI() __asm__ volatile("cli")
#define STI() __asm__ volatile("sti")
#define HLT() __asm__ volatile("hlt")
#define IRET() __asm__ volatile("iret")

#define switch_to_user_mode() \
    __asm__ volatile(" \
        cli\n \
        mov $0x23, %ax\n \
        mov %ax, %ds\n \
        mov %ax, %es\n \
        mov %ax, %fs\n \
        mov %ax, %gs\n \
        \n \
        mov %esp, %eax\n \
        pushl $0x23\n \
        pushf\n \
        pushl $0x1B\n \
        push $1f\n \
        iret\n \
        1:\n \
    ")

#endif