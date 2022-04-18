#pragma once

#include "../utils/inttypes.h"

#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

#define low_16(address) (uint16)((address) & 0xFFFF)
#define high_16(address) (uint16)(((address) >> 16) & 0xFFFF)

typedef struct 
{
    uint16 low_offset;
    uint16 sel;
    uint8 always0;
    uint8 flags;
    uint16 high_offset;
} __attribute__((packed)) idt_gate_t;

typedef struct 
{
    uint16 limit;
    uint32 base;
} __attribute__((packed)) idt_register_t;

void set_idt_gate(int n, uint32 handler);
void load_idt();