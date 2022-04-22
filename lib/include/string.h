#ifndef LUMAOS_STRING_H_
#define LUMAOS_STRING_H_

#pragma once

#include "stdint.h"

int64_t strlen(const char *str);
void strappchr(char str[], char c);
int8_t strcmp(const char *str1, const char *str2);
char *strcpy(char *target, char *source);
int8_t strback(char *str);
void inttostr(int16_t n, char *str);
void strrev(char *str);

#endif