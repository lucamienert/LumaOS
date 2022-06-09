#include <kernel/cpu/gdt.h>
#include <kernel/cpu/tss.h>

#define MAX_ENTRIES 6

extern void gdt_flush(uint32_t);

gdt_entry_t entries[MAX_ENTRIES];
gdt_pointer_t pointer;

void gdt_init()
{
    pointer.limit = (sizeof(gdt_entry_t) * MAX_ENTRIES) - 1;
    pointer.base = (uint32_t) &entries;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    tss_write(5, 0x10, 0x0);

    gdt_flush((uint32_t) &pointer);
    tss_flush();
}

void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    entries[num].base_low = base & 0xFFFF;
    entries[num].base_middle = (base >> 16) & 0xFF;
    entries[num].base_high = (base >> 24) & 0xFF;

    entries[num].limit_low = limit & 0xFFFF;
    entries[num].granularity = (limit >> 16) & 0x0F;
    
    entries[num].granularity |= gran & 0xF0;
    entries[num].access = access;
}