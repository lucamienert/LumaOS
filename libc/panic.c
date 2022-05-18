#include <panic.h>

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
