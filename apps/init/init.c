#include "../../include/libc/stdio.h"

int main(int argc, char **argv)
{
    printf("Hello World!");

    while(1) __asm__ volatile("nop");

    return 0;
}