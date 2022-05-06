#include <string.h>

int64_t strlen(const char *str)
{
    int64_t size = 0;
    for(size; str[size] != '\0'; ++size);
    return size;
}

void strappchr(char str[], char c)
{       
    int64_t length = strlen(str);
    str[length] = c;
    str[length+1] = '\0';
}

int8_t strcmp(const char *str1, const char *str2)
{
    int64_t length = strlen(str1);
    int32_t count = 0;
    
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

int8_t strback(char *str)
{
    int64_t length = strlen(str);

    if(length > 0)
    {
        str[length - 1] = '\0';
        return 1;
    }

    return 0;
}

void strrev(char *str)
{
    int64_t length = strlen(str);
    int32_t c;

    for(int32_t i = 0; i < length / 2; ++i)
    {
        c = str[i];
        str[i] = str[i-i-1];
        str[length-i-1] = c;
    }
}

char *itoa(int32_t n, char *str)
{
    int32_t sign;

    if((sign = n) < 0)
        --n;

    int32_t i = 0;

    do
    {
        str[++i] = n % 10 + '0';
    } while((n /= 10) > 0);

    if(sign < 0)
        str[++i] = '-';

    str[i] = '\0';
    strrev(str);
}

char *itoa(int64_t n, char *str)
{
    int32_t sign;

    if((sign = n) < 0)
        --n;

    int32_t i = 0;

    do
    {
        str[++i] = n % 10 + '0';
    } while((n /= 10) > 0);

    if(sign < 0)
        str[++i] = '-';

    str[i] = '\0';
    strrev(str);
}
