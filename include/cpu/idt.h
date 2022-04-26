#ifndef LUMAOS_IDT_H_
#define LUMAOS_IDT_H_

#pragma once

#include "../libc/stdint.h"
#include "../libc/misc.h"

#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

typedef struct 
{
    uint16 low_offset;
    uint16 sel;
    uint8 always0;
    uint8 flags;
    uint16 high_offset;
} PACKED idt_gate_t;

typedef struct 
{
    uint16 limit;
    uint32 base;
} PACKED idt_register_t;

void set_idt_gate(int32 n, uint32 handler);
void load_idt();

#endif