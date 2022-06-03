#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Console");

    while(1) __asm__ volatile("nop");

    return 0;
}
