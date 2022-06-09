#ifndef LUMAOS_GDT_H_
#define LUMAOS_GDT_H_

#pragma once

#include <stdint.h>

typedef struct GDTEntry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct GDTPointer
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_pointer_t;

void init_gdt();
void set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif