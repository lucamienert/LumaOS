#include "../include/libc/stdlib.h"

void memcpy(void *source, void *dest, size_t nbytes)
{
    int32 i;
    for (i = 0; i < nbytes; ++i)
        *(dest + i) = *(source + i);
}

void memset(void *dst, uint8 value, size_t nbytes)
{
    uint8 *d = dst;
    while (nbytes-- > 0)
        *d++ = value;
}

/**
 * Replace with memory functions
 */

static void initialize()
{
    freeList->size = SIZE - sizeof(struct Block);
    freeList->free = 1;
    freeList->next = NULLPTR;
} 

static void split(struct Block *slot, uint64 size)
{
    struct Block *block = slot + size + sizeof(struct Block);
    block->size = (slot->size) - size - sizeof(struct Block);
    block->free = 1;
    block->next = slot->next;

    slot->size = size;
    slot->free = 0;
    slot->next = block;
}

void *malloc(uint64 bytes)
{
    struct Block *cur, *prev;
    void *result;

    if(!(freeList->size))
        initialize();

    cur = freeList;

    while((cur->size < bytes) || ((cur->free == 0) && (cur->next != (void*)0)))
    {
        prev = cur;
        cur = cur->next;
    }

    if(cur->size == bytes)
    {
        cur->free = 0;
        result = (void*)(++cur);
        return result;
    }
    else if(cur->size < bytes + sizeof(struct Block))
    {
        split(cur, bytes);
        result = (void*)(++cur);
        return result;
    }
    
    result = NULLPTR;
    return result;
}

static uint64 get_size(void *ptr)
{
    uint64 *in = ptr;

    if(!in)
        return -1;

    --in;
    return *in;
}

static void merge()
{
    struct Block *cur, *prev;
    cur = freeList;

    while(cur->free != 0)
    {
        if(cur->free && cur->next->free)
        {
            cur->size += cur->next->size + sizeof(struct Block);
            cur->next = cur->next->next;
        }

        prev = cur;
        cur = cur->next;
    }
}

void free(void *ptr)
{
    if(ptr == NULLPTR)
        return;
        
    if(((void*) memory > ptr) && (ptr > (void*)(memory + SIZE)))
        return;
    
    struct Block *cur = ptr;
    --cur;
    cur->free = 1;
    merge();
}

void *realloc(void *ptr, uint64 size)
{
    void *new;
    int64 msize = get_size(ptr);

    if(size <= msize)
        return ptr;

    new = malloc(size);
    memory_copy(new, ptr, msize);
    free(ptr);
    return new;
}