#include "../include/cpu/timer.h"
#include "../include/cpu/isr.h"
#include "../include/drivers/display.h"
#include "../include/drivers/ports.h"
#include "../include/utils/string.h"

uint32 tick = 0;

static void timer_callback(registers_t *regs) {
    ++tick;
    print("Tick: ");

    char tick_ascii[256];
    inttostr(tick, tick_ascii);
    print(tick_ascii);
    print_nl();
}

void init_timer(uint32 freq)
{
    register_interrupt_handler(IRQ0, timer_callback);

    uint32 divisor = 1193180 / freq;
    uint8 low  = (uint8)(divisor & 0xFF);
    uint8 high = (uint8)((divisor >> 8) & 0xFF);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}