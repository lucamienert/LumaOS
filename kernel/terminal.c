#include "../include/kernel/terminal.h"
#include "../include/drivers/display.h"
#include "../include/utils/string.h"
#include "../include/utils/inttypes.h"

void init_terminal()
{
    print("LumaOS > ");
}

void execute_command(char *command)
{
    if(strcmp(command, "EXIT") == 0)
    {
        print("Shutting down LumaOS!\n");
        asm volatile("hlt");
    }
    else if(strcmp(command, "REBOOT") == 0)
    {
        print("Trying to reboot LumaOS!\n");
    } 
    
    print("Unknown command: ");
    print(command);
    print_nl();
    init_terminal();
}