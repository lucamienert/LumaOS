#pragma once

#include "../utils/inttypes.h"
#include "../utils/null.h"

#define SIZE 50000

char memory[SIZE];

struct Block
{
    uint64 size;
    int32 free;
    struct Block *next;
};

struct Block *freeList = (void*) memory;

void memory_copy(uint8 *source, uint8 *dest, uint32 nbytes);
void *malloc(uint64 bytes);
void free(void *ptr);