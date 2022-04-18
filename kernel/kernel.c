#include "../include/kernel/kernel.h"
#include "../include/cpu/isr.h"
#include "../include/drivers/keyboard.h"
#include "../include/drivers/display.h"
#include "../include/kernel/terminal.h"

void init_kernel()
{
    clear_screen();
    
    print("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print("Enabling external interrupts.\n");
    asm volatile("sti");

    print("Initializing keyboard (IRQ 1).\n");
    init_keyboard();
    
    clear_screen();
}

void main()
{
    init_kernel();
    init_terminal();
}