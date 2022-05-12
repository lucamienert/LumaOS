#include <gui/draw.h>
#include <gui/font.h>
#include <gui/inc.h>

#include <string.h>

uint32_t *pixel_offset(fb_t fb, uint32_t x, uint32_t y)
{
    return (uint32_t*) (fb.address + y * fb.pitch + x * fb.bpp / 8);
}

void draw_pixel(fb_t fb, int32_t x, int32_t y, uint32_t col)
{
    uint32_t *offset = pixel_offset(fb, x, y);
    *offset = col;
}

void draw_rect(fb_t fb, int32_t x, int32_t y, int32_t width, int32_t height, uint32_t col)
{
    uint32_t *offset = pixel_offset(fb, x, y);

    for(int32_t i = 0; i < height; ++i)
    {
        for(int32_t j = 0; j < width; ++j)
            offset[j] = col;

        offset = (uint32_t*)((uint64_t) offset + fb.pitch);
    }
}

void draw_line(fb_t fb, int32_t x, int32_t y, int32_t x2, int32_t y2, uint32_t col)
{

}

void draw_char(fb_t fb, char c, int32_t x, int32_t y, uint32_t col)
{

}

void draw_string(fb_t fb, char *str, int32_t x, int32_t y, uint32_t col)
{

}
