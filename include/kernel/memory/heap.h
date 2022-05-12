#ifndef LUMAOS_HEAP_H_
#define LUMAOS_HEAP_H_

#pragma once

#include <list.h>
#include <stdint.h>

#include <kernel/paging.h>

#define HEAP_START 0xC0000000
#define HEAP_INITIAL_SIZE 0x100000
#define HEAP_INDEX_SIZE 0x20000
#define HEAP_MAGIC 0x123890AB
#define HEAP_MIN_SIZE 0x70000

typedef struct Header
{
    uint32_t magic;
    uint32_t size;
    uint8_t is_hole;
} header_t;

typedef struct Footer
{
    uint32_t magic;
    header_t *header;
} footer_t;

typedef struct Heap
{
    ordered_list_t index;
    uint32_t start_address;
    uint32_t end_address;
    uint32_t max_address;
    uint8_t supervisor;
    uint8_t readonly;
} heap_t;

heap_t *create_heap(uint32_t start, uint32_t end_addr, uint32_t max, uint8_t supervisor, uint8_t readonly);
void *halloc(uint32_t size, uint8_t page_align, heap_t *heap);
void hfree(void *p, heap_t *heap);
uint32_t kmalloc_int(uint32_t size, int align, uint32_t *phys);
uint32_t kmalloc_a(uint32_t size);
uint32_t kmalloc_p(uint32_t size, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t size, uint32_t *phys);
uint32_t kmalloc(uint32_t size);
void kfree(void *p);

#endif