#include "../include/kernel/terminal.h"
#include "../include/drivers/display.h"
#include "../include/utils/string.h"
#include "../include/utils/inttypes.h"

static const uint64 hash(const char *str) {
    uint64 hash = 5381;  
    int32 c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void init_terminal()
{
    print("LumaOS > ");
}

void execute_command(char *command)
{
    switch(hash(command))
    {
        case EXIT:
            print("Shutting down LumaOS!\n");
            asm volatile("hlt");
            break;
        case REBOOT:
            print("Trying to reboot LumaOS!\n");
            // TODO
            break;
        default:
            break; 
    }
    
    print("Unknown command: ");
    print(command);
    print_nl();
    init_terminal();
}