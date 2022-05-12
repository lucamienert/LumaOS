#ifndef LUMAOS_PAGING_H_
#define LUMAOS_PAGING_H_

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <panic.h>
#include <kernel/cpu/isr.h>

#define INDEX_FROM_BIT(a) (a / (8 * 4))
#define OFFSET_FROM_BIT(a) (a % (8 * 4))

typedef struct Page
{
    uint32_t present : 1;
    uint32_t rw : 1;
    uint32_t user : 1;
    uint32_t accessed : 1;
    uint32_t dirty : 1;
    uint32_t unused : 7;
    uint32_t frame : 20;
} page_t;

typedef struct PageTable
{
    page_t pages[1024];
} page_table_t;

typedef struct PageDirectory
{
    page_table_t *tables[1024];
    uint32_t tablesPhysical[1024];
    uint32_t physicalAddr;
} page_directory_t;

void init_paging();
void switch_page_directory(page_directory_t *newDir);
void alloc_frame(page_t *page, int32_t is_kernel, int32_t is_writable);
void free_frame(page_t *page);
page_t *get_page(uint32_t address, int32_t make, page_directory_t *dir);
void page_fault(registers_t *regs);
page_directory_t *clone_directory(page_directory_t *src);

#endif