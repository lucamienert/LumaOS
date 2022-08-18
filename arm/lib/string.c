#include <string.h>

int64_t strlen(const char *str)
{
    int64_t size = 0;
    for(size; str[size] != '\0'; ++size);
    return size;
}

void itoa(unsigned i, unsigned base, char *buf);
{
    int32_t pos = 0;
    int32_t opos = 0;
    int32_t top = 0;

    if (i == 0 || base > 16) 
    {
    	buf[0] = '0';
    	buf[1] = '\0';
    	return;
    }

    while (i != 0) 
    {
    	tbuf[pos] = bchars[i % base];
    	pos++;
    	i /= base;
    }

    top=pos--;
    for (opos=0; opos<top; pos--,opos++)
    	buf[opos] = tbuf[pos];

    buf[opos] = 0;
}