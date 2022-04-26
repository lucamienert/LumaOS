#include "../include/libc/stdio.h"

void printf(char *str)
{
    print(str);
}

extern void panic(const char *message, const char *file, uint32 line)
{
    CLI();
    printf("[PANIC]: Exiting...");
    HLT();
}

extern void panic_assert(const char *file, uint32 line, const char *desc)
{
    CLI();
    printf("[ASSERTION FAILURE]: Exiting...");
    HLT();
}