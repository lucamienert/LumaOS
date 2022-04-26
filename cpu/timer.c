#include "../include/cpu/timer.h"
#include "../include/cpu/isr.h"
#include "../include/drivers/display.h"
#include "../include/drivers/ports.h"
#include "../include/libc/string.h"

uint32 tick = 0;

static void timer_callback(registers_t *regs) {
    ++tick;
}

void init_timer(uint32 freq)
{
    register_interrupt_handler(IRQ0, timer_callback);

    uint32 divisor = HZ / freq;
    uint8 low  = low_8(divisor);
    uint8 high = high_8(divisor);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}