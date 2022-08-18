#include <drivers/display.h>

struct Display *debugDisplay = 0;
struct Display *currentDisplay = 0;

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

struct Display create(char c, uint8_t flags, char *name)
{
    struct Display display;
    display.putc = c;
    display.flags = flags;
    display.name = name;

    return display;
}

void display_init(struct Display *display)
{
    if(display->flags & 1)
        debugDisplay = display;
    
    if(display->flags & 2)
        currentDisplay = display;
}

void display_put(uint8_t level, char c)
{
    if(level == KERNEL_ERROR)
        debugDisplay->putc(c)

    currentDisplay->putc(c);
}

void display_print(uint8_t level, char *str)
{
    while(*str)
        display_put(level, *str++);

    return;
}

void print_tty(char *str, ...)
{
    char *s = 0;
    uint32_t level = 1;

    va_list ap;
    va_start(ap, str);

    for(size_t i = 0; i < strlen(str); ++i)
    {
        if(str[i] == '%')
        {
            switch(str[i + 1])
            {
                case 's':
                    s = va_arg(ap, char *);
                    display_print(level, s);
                    ++i;
                    continue;
                
                case 'd':
                    int32_t c = va_arg(ap, int);
                    char buf[32] = {0};
                    itoa(c, 10, buf);
                    display_print(level, buf);
                    ++i;
                    continue;
            }
        }
        display_put(level, str[i]);
    }
    va_end(ap);
}