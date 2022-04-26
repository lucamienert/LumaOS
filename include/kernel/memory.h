#ifndef LUMAOS_MEMORY_H_
#define LUMAOS_MEMORY_H_

#pragma once

#include "../libc/stdint.h"
#include "../libc/stdnull.h"

#define SIZE 50000

static char memory[SIZE];

struct Block
{
    uint64 size;
    int32 free;
    struct Block *next;
};

static struct Block *freeList = (void*) memory;

void memory_copy(uint8 *source, uint8 *dest, uint32 nbytes);
void *malloc(uint64 bytes);
void free(void *ptr);
void *realloc(void *ptr, uint64 size);

#endif