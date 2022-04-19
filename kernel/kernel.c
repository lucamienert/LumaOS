#include "../include/kernel/kernel.h"
#include "../include/cpu/isr.h"
#include "../include/drivers/keyboard.h"
#include "../include/drivers/display.h"
#include "../include/kernel/terminal.h"

const char *str =
" _                            ____   _____ \n"\
"| |                          / __ \\ / ____|\n"\
"| |    _   _ _ __ ___   __ _| |  | | (___  \n"\
"| |   | | | | '_ ` _ \\ / _` | |  | |\\___ \\ \n"\
"| |___| |_| | | | | | | (_| | |__| |____) |\n"\
"|______\\__,_|_| |_| |_|\\__,_|\\____/|_____/ \n";

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

    print(str);
}

void main()
{
    init_kernel();
    init_terminal();
}
