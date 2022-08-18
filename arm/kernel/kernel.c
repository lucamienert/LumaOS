#include <kernel/kernel.h>

#include <drivers/display.h>
#include <drivers/pl110.h>
#include <drivers/serial.h>

int kernel_main(void)
{
    serial_init();    
    pl110_init();

    print_tty("LumaOS ARM Test\n");
    print_tty("Reached end of kernel_main()\n");

    return 0;
}