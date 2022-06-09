#include <kernel/cpu/tss.h>
#include <kernel/cpu/gdt.h>

extern void tss_flush();

tss_entry_t entry;

void set_kernel_stack(uint32_t stack)
{
    entry.esp0 = stack;
}

void tss_write(int32_t num, uint16_t ss0, uint32_t esp0)
{
    uint32_t base = (uint32_t) &entry;
    uint32_t limit = base + sizeof(entry);

    gdt_set_gate(num, base, limit, 0xE9, 0x00);

    memset(&entry, 0, sizeof(entry));

    entry.ss0  = ss0;
    entry.esp0 = esp0;
    
    entry.cs = 0x0b;     
    entry.ss = entry.ds = entry.es = entry.fs = entry.gs = 0x13;
}