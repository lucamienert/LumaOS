#include <drivers/keyboard.h>
#include <drivers/display.h>

#include <kernel/cpu/isr.h>
#include <kernel/tty.h>

#include <string.h>
#include <asm/ports.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SC_MAX 57

static char key_buffer[256];

const char *sc_name[] = 
{   
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
    "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
    "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
    "/", "RShift", "Keypad *", "LAlt", "Spacebar"
};

const char sc_ascii[] = 
{
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
    'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '
};

static void keyboard_callback(registers_t *regs) 
{
    uint8 scancode = port_byte_in(0x60);

    if (scancode > SC_MAX) 
        return;

    if (scancode == BACKSPACE) 
    {
        if (strback(key_buffer))
            print_backspace();    
    } 
    else if (scancode == ENTER) 
    {
        print_nl();
        execute_command(key_buffer);
        key_buffer[0] = '\0';
    } 
    else 
    {
        char letter = sc_ascii[(int32) scancode];
        strappchr(key_buffer, letter);
        char str[2] = {
            letter, 
            '\0'
        };
        print(str);
    }
}

void init_keyboard() 
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}
