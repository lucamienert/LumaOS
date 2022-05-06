#include <kernel/cpu/timer.h>
#include <kernel/cpu/isr.h>
#include <asm/ports.h>
#include <system/misc.h>

uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
    ++tick;
}

void init_timer(uint32_t freq)
{
    register_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = HZ / freq;
    uint8_t low  = low_8(divisor);
    uint8_t high = high_8(divisor);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}