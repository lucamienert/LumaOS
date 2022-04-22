#include "include/stdio.h"

void printf(char *str)
{
    // print_screen(str);
}

extern void panic(const char *message, const char *file, uint32_t line)
{
    CLI();
    printf("[PANIC]: Exiting...");
    HLT();
}

extern void panic_assert(const char *file, uint32_t line, const char *desc)
{
    CLI();
    printf("[ASSERTION FAILURE]: Exiting...");
    HLT();
}