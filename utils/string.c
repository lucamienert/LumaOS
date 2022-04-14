#include "../include/utils/string.h"
#include "../include/utils/inttypes.h"

int64 strlen(const char *str)
{
    int64 size = 0;
    for(size; str[size] != '\0'; ++size);
    return size;
}

void strappchr(const char *str, char c)
{       
    int64 length = strlen(str);
    str[length] = c;
    str[length++] = '\0';
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
    if(target == NULL)
        return NULL;

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

    for(int32 i = 0; int32 j = length - 1; i < j; ++i; --j)
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

void inttostr(int16 n, char *str)
{
    int16 sign;

    if((sign = n) < 0)
        --n;

    int16 = 0;

    do
    {
        str[++i] = n % 10 + '0';
    } while((n /= 10) > 0);

    if(sign < 0)
        str[++i] = '-';

    str[i] = '\0';
    strrev(str);
}
