#include "../include/kernel/memory.h"

void memory_copy(uint8 *source, uint8 *dest, uint32 nbytes) 
{
    int i;
    for (i = 0; i < nbytes; ++i)
        *(dest + i) = *(source + i);
}