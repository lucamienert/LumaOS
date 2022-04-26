#include "../include/kernel/terminal.h"
#include "../include/drivers/display.h"
#include "../include/utils/string.h"

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

/* Commands */
static void exit();
static void reboot();
static void pwd();
static void shell();
static void ls();
static void cd();
static void touch();
static void mkdir();
static void rm();

void execute_command(char *command)
{
    switch(hash(command))
    {
        case EXIT: exit(); break;
        case REBOOT: reboot(); break;
        case PWD: pwd(); break;
        case SHELL: shell(); break;
        case LS: ls(); break;
        case CD: cd(); break;
        case TOUCH: touch(); break;
        case MKDIR: mkdir(); break;
        case RM: rm(); break;
        default: break;
    }
    
    print("Unknown command: ");
    print(command);
    print_nl();
    init_terminal();
}

static void exit()
{
    print("Shutting down\n");
    asm volatile("hlt");
}

static void reboot()
{
    print("Trying to reboot LumaOS!\n");
}

static void pwd()
{
    print("/");
}

static void shell()
{
    clear_screen();
    init_terminal();
}

static void ls()
{
    print("NOT IMPLEMENTED");
}

static void cd()
{
    print("NOT IMPLEMENTED");
}

static void touch()
{
    print("NOT IMPLEMENTED");
}

static void mkdir()
{
    print("NOT IMPLEMENTED");
}

static void rm()
{
    print("NOT IMPLEMENTED");
}
