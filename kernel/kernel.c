#include "../include/kernel/kernel.h"
#include "../include/kernel/terminal.h"
#include "../include/drivers/diplay.h"

void init_kernel()
{
    clear_screen();
    print("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print("Enabling external interrupts.\n");
    asm volatile("sti");

    print("Initializing keyboard (IRQ 1).\n");
    init_keyboard();

    print("Initializing dynamic memory.\n");
    init_dynamic_mem();
    
    clear_screen();
}

void main()
{
    init_kernel();
    init_terminal();
}