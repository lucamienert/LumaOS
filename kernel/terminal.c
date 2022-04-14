#include "../include/kernel/terminal.h"
#include "../include/drivers/display.h"
#include "../include/utils/string.h"
#include "../include/utils/inttypes.h"

void init_terminal()
{
    clear_screen();
    print("LumaOS > ");
}

void execute_command(char *command)
{
    if(strcmp(command, "EXIT") == 1)
    {
        print("Shutting down LumaOS!\n");
        asm volatile("hlt");
    }
    else if(strcmp(command, "REBOOT") == 1)
    {
        print("Trying to reboot LumaOS!\n");
        // Halt for the moment
        asm volatile("hlt");
    }

    print("Unknown command: ");
    print(command);
    print_nl();
    init_terminal();
}