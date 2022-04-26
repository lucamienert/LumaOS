#include "../include/libc/string.h"

int64 strlen(const char *str)
{
    int64 size = 0;
    for(size; str[size] != '\0'; ++size);
    return size;
}

void strappchr(char str[], char c)
{       
    int64 length = strlen(str);
    str[length] = c;
    str[length+1] = '\0';
}

int8 strcmp(const char *str1, const char *str2)
{
    int64 length = strlen(str1);
    int32 count = 0;
    
    while(*str1++ != '\0' && *str2++ != '\0')
    {
        if(*str1 == *str2)
            ++count;
    }

    return count == length ? 0 : 1;
}

char *strcpy(char *target, char *source)
{
    while(*source != '\0')
        *target++ = *source++;

    *target = '\0';
    return target;
}

int8 strback(char *str)
{
    int64 length = strlen(str);

    if(length > 0)
    {
        str[length - 1] = '\0';
        return 1;
    }

    return 0;
}

void strrev(char *str)
{
    int64 length = strlen(str);
    int32 c;

    for(int32 i = 0; i < length / 2; ++i)
    {
        c = str[i];
        str[i] = str[i-i-1];
        str[length-i-1] = c;
    }
}

void inttostr(int16 n, char *str)
{
    int16 sign;

    if((sign = n) < 0)
        --n;

    int16 i = 0;

    do
    {
        str[++i] = n % 10 + '0';
    } while((n /= 10) > 0);

    if(sign < 0)
        str[++i] = '-';

    str[i] = '\0';
    strrev(str);
}
