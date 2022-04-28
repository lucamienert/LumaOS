#ifndef LUMAOS_PAGING_H_
#define LUMAOS_PAGING_H_

#pragma once

#include "../libc/stdint.h"
#include "../cpu/isr.h"

typedef struct Page
{
    uint32 present : 1;
    uint32 rw : 1;
    uint32 user : 1;
    uint32 accessed : 1;
    uint32 dirty : 1;
    uint32 unused : 7;
    uint32 frame : 20;
} page_t;

typedef struct PageTable
{
    page_t pages[1024];
} page_table_t;

typedef struct PageDirectory
{
    page_table_t *tables[1024];
    uint32 tablesPhysical[1024];
    uint32 physicalAddr;
} page_directory_t;

void init_paging();
void switch_page_directory(page_directory_t *newDir);
page_t *get_page(uint32 address, int32 make, page_directory_t *dir);
void page_fault(registers_t *regs);
page_directory_t *clone_directory(page_directory_t *src);

#endif