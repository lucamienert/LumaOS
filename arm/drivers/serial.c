#include <drivers/serial.h>

#define volatile unsigned long vul
#define MAX 80

static int count = 0;

void serial_put(char c)
{
    if (c == '\n')
	{
		for(; count < MAX;)
			serial_putc(' ');

		count = 0;
		return;
	}
	
    while (*(vul*)(SERIAL_BASE + SERIAL_FLAG_REGISTER) & (SERIAL_BUFFER_FULL));

	*(vul*) SERIAL_BASE = c;
	++count;
}

void serial_init()
{
	struct Display serial_display = create(
		serial_put,
		3,
		"Serial output display"
	);

    display_init(&serial_display);
}