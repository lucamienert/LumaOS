#include <kernel/kernel.h>
#include <kernel/task.h>
#include <kernel/syscall.h>

#include <kernel/memory/paging.h>

#include <kernel/cpu/gdt.h>
#include <kernel/cpu/idt.h>
#include <kernel/cpu/timer.h>

#include <driver/keyboard.h>

#include <fs/filesystem.h>
#include <fs/initramdisk.h>

#include <asm/system.h>
#include <system/multiboot.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#if !defined(__i386__)
#error "Must be compiled with i386-elf compiler!"
#endif

#define HANDLERS 256
#define TIMER 50

extern isr_t interrupt_handlers[];
extern uint32_t placement_address;

uint32_t initial_esp;

char *str =
" _                            ____   _____ \n"\
"| |                          / __ \\ / ____|\n"\
"| |    _   _ _ __ ___   __ _| |  | | (___  \n"\
"| |   | | | | '_ ` _ \\ / _` | |  | |\\___ \\ \n"\
"| |___| |_| | | | | | | (_| | |__| |____) |\n"\
"|______\\__,_|_| |_| |_|\\__,_|\\____/|_____/ \n";

int main(multiboot_t *mboot_ptr, uint32_t initial_stack)
{
    initial_esp = initial_stack;

    gdt_init();
    printf("[Init] GDT...");
    idt_init();
    printf("[Init] IDT...");
    memset(&interrupt_handlers, 0, sizeof(isr_t) * HANDLERS);

    cls();

    STI();
    timer_init(TIMER);
    printf("[Init] Timer...");

    //ASSERT(mboot_ptr->mods_count > 0);

    uint32_t initrd_location = *((uint32_t*) mboot_ptr->mods_addr);
    uint32_t initrd_end = *(uint32_t*)(mboot_ptr->mods_addr + 4);

    placement_address = initrd_end;

    init_paging();
    printf("[Init] Paging...");
    init_tasking();
    printf("[Init] Tasking...");

    filesystem_root = init_initial_ram_disk();
    printf("[Init] Ramdisk...");

    init_syscalls();
    printf("[Init] Syscalls...");

    switch_to_user_mode();
    printf("[Init] Switching to User Mode...");

    init_keyboard();
    printf("[Init] Keyboard...");

    printf("%s\n", str);
    printf("LumaOS - by Luca Mienert (Copyright 2022)");

    init_terminal();

    return 0;
}
