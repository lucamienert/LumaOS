#include <drivers/display.h>
#include <asm/ports.h>
#include <kernel/heap.h>
#include <string.h>

static void set_cursor(int32 offset) 
{
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (uint8) (offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (uint8) (offset & 0xff));
}

static int32 get_cursor() 
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int32 offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

static int32 get_offset(int32 col, int32 row) 
{
    return 2 * (row * MAX_COLS + col);
}

static int32 get_row_from_offset(int32 offset) 
{
    return offset / (2 * MAX_COLS);
}

static int32 move_offset_to_new_line(int32 offset) 
{
    return get_offset(0, get_row_from_offset(offset) + 1);
}

static void set_char_at_video_memory(char character, int32 offset) 
{
    uint8 *vidmem = (uint8*) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_ON_BLACK;
}

void print(char *str)
{
    int32 offset = get_cursor();
    int32 i = 0;
    while (str[i] != 0) 
    {
        if (offset >= MAX_ROWS * MAX_COLS * 2)
            offset = scroll_ln(offset);
        
        if (str[i] == '\n')
            offset = move_offset_to_new_line(offset);
        else 
        {
            set_char_at_video_memory(str[i], offset);
            offset += 2;
        }

        ++i;
    }
    set_cursor(offset);
}

void print_nl()
{
    int32 newOffset = move_offset_to_new_line(get_cursor());

    if (newOffset >= MAX_ROWS * MAX_COLS * 2)
        newOffset = scroll_ln(newOffset);

    set_cursor(newOffset);
}

void clear_screen()
{
    int screen_size = MAX_COLS * MAX_ROWS;

    for (int i = 0; i < screen_size; ++i)
        set_char_at_video_memory(' ', i * 2);

    set_cursor(get_offset(0, 0));
}

int8 scroll_ln(int8 offset)
{
    memory_copy(
        (uint8 * )(get_offset(0, 1) + VIDEO_ADDRESS),
        (uint8 * )(get_offset(0, 0) + VIDEO_ADDRESS),
        MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int32 col = 0; col < MAX_COLS; col++)
        set_char_at_video_memory(' ', get_offset(col, MAX_ROWS - 1));

    return offset - 2 * MAX_COLS;
}

void print_backspace()
{
    int32 newCursor = get_cursor() - 2;
    set_char_at_video_memory(' ', newCursor);
    set_cursor(newCursor);
}
