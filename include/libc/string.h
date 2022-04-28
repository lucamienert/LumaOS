#ifndef LUMAOS_STRING_H_
#define LUMAOS_STRING_H_

#pragma once

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

int64 strlen(const char *str);
void strappchr(char str[], char c);
int8 strcmp(const char *str1, const char *str2);
char *strcpy(char *target, char *source);
int8 strback(char *str);
void inttostr(int16 n, char *str);
void strrev(char *str);

#ifdef __cplusplus
}
#endif

#endif