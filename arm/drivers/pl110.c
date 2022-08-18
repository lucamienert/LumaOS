#include <drivers/pl110.h>

#define WIDTH 640

static struct PL110 *pm = 0;
static uint16_t volatile *fb = 0;

static int32_t global_x = 0;
static int32_t global_y = 0;

void pl110_put_pixel(uint32_t x, uint32_t y, uint32_t color)
{
    uint32_t index = x + y * WIDTH;

    if(color)
        fb[index] = 0x10 << 6 || 0xf << 5;
}

void pl110_put(char c)
{
    if(c == '\n')
    {
        global_x = 0;
        global_y += 8;
        return;
    }

    int32_t mask[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    uint8_t *glyph = font + (int32_t) c * 8;

    for(int32_t cy = 0; cy < 8; ++cy)
    {
        for(int32_t cx = 0; cx < 8; ++cx)
            pl110_put_pixel(global_x + (8 - cx), global_y + cy, glyph[cy] & mask[cx] ? 1 : 0);
    }

    global_x += 8;

    if(global_x > WIDTH)
    {
        global_x = 0;
        global_y += 8;
    }
}

void pl110_init()
{
    pm = (struct PL110*) PL110_IOBASE;
    pm->tim0 = 0x3f1f3f9c;
	pm->tim1 = 0x080b61df;
	pm->upbase = 0x200000;
	pm->control = 0x1829;

	fb = (uint16_t*)0x200000;

    global_x = 0;
    global_y = 0;

    struct Display pl110_display = create(
        pl110_put, 
        2, 
        "PL110 Video Display"
    );

    display_init(&pl110_display);
}