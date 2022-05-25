#include <drivers/display.h>
#include <asm/ports.h>

uint16_t *video_memory = (uint16_t*) VIDEO_ADDRESS;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

static void display_move_cursor()
{
    uint16_t cursorLocation = cursor_y * SCREEN_WIDTH + cursor_x;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, cursorLocation >> 8);
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, cursorLocation);
}

static void display_scroll()
{
    uint8_t attributeByte = (BLACK << 4) | (WHITE & 0x0F);
    uint16_t black = 0x20 | (attributeByte << 8);

    if(cursor_y >= SCREEN_HEIGHT)
    {
        for(int32_t i = 0; i < (SCREEN_HEIGHT - 1) * SCREEN_HEIGHT; ++i)
            video_memory[i] = video_memory[i + SCREEN_WIDTH];

        for(int32_t i = (SCREEN_WIDTH - 1) * SCREEN_HEIGHT; i < SCREEN_HEIGHT * SCREEN_WIDTH; ++i)
            video_memory[i] = blank;

        cursor_y = (SCREEN_HEIGHT - 1);
    }
}

void display_put(char c)
{
    uint8_t backColour = BLACK;
    uint8_t foreColour = WHITE;

    uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);

    uint16_t attribute = attributeByte << 8;
    uint16_t *location;

    if (c == 0x08 && cursor_x)
        --cursor_x;
    else if (c == 0x09)
        cursor_x = (cursor_x+8) & ~(8-1);
    else if (c == '\r')
        cursor_x = 0;
    else if (c == '\n')
    {
        cursor_x = 0;
        ++cursor_y;
    }
    else if(c >= ' ')
    {
        location = video_memory + (cursor_y * SCREEN_WIDTH + cursor_x);
        *location = c | attribute;
        ++cursor_x;
    }

    if(cursor_x >= SCREEN_WIDTH)
    {
        cursor_x = 0;
        ++cursor_y;
    }

    display_scroll();
    display_move_cursor();
}

void display_print(char *str)
{
    int32_t i = 0;
    while(str[i])
        display_put(c[i++]);
}

void display_clear()
{
    uint8_t attributeByte = (BLACK << 4) | (WHITE & 0x0F);
    uint16_t blank = 0x20 | (attributeByte << 8);

    for(int32_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; ++i)
        video_memory[i] = blank;

    cursor_x = 0;
    cursor_y = 0;
    display_move_cursor();
}

void display_backspace()
{
    --cursor_x;
    display_put(' ');
    display_move_cursor();
}
