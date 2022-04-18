#include "../include/drivers/ports.h"

uint8 port_byte_in(uint16 port)
{
    unsigned char result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(uint16 port, uint8 data)
{
    asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint16 port_word_in(uint16 port)
{
    unsigned short result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out(uint16 port, uint16 data)
{
    asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}