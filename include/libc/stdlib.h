#ifndef LUMAOS_STDLIB_H_
#define LUMAOS_STDLIB_H_

#pragma once

#include "stdint.h"
#include "stdnull.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SIZE 50000

static char memory[SIZE];

struct Block
{
    uint64 size;
    int32 free;
    struct Block *next;
};

static struct Block *freeList = (void*) memory;

void memcpy(void *source, void *dest, size_t nbytes);
void memset(void *dst, uint8_t value, size_t nbytes);

void *malloc(uint64 bytes);
void free(void *ptr);
void *realloc(void *ptr, uint64 size);

#ifdef __cplusplus
}
#endif

#endif