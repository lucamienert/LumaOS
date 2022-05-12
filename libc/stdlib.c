#include <stdlib.h>
#include <kernel/memory/heap.h>

void memcpy(void *source, void *dest, size_t nbytes)
{

}

void memset(void *dst, uint8_t value, size_t nbytes)
{
}

void malloc(uint32_t size)
{
    kmalloc(size);
}

void free(void *item)
{
    kfree(item);
}
