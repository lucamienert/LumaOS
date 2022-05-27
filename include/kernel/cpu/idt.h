#ifndef LUMAOS_IDT_H_
#define LUMAOS_IDT_H_

#pragma once

#include <stdint.h>

#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

typedef struct IDTEntry
{
    uint8_t always0;
    uint8_t flags;
    uint16_t low_offset;
    uint16_t sel;
    uint16_t high_offset;
} __attribute__((packed)) idt_entry_t;

typedef struct IDTPointer
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_pointer_t;

extern void idt_flush(uint32_t);

void idt_set_gate(int32_t n, uint32_t base, uint16_t sel, uint8_t flags);
void idt_init();

#endif