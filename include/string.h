/*
    NOTE:

    This is created by myself. Its only purpose is to provide string functions
    for the operating system and libraries like LTK and LUI.

    It does not follow the ISO standard
*/
#ifndef LUMAOS_STRING_H_
#define LUMAOS_STRING_H_

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int64_t strlen(const char *str);
void strappchr(char str[], char c);
int8_t strcmp(const char *str1, const char *str2);
char *strcpy(char *target, char *source);
int8_t strback(char *str);
void strrev(char *str);

char *itoa(int32_t n);
char *ltoa(int64_t n);

#ifdef __cplusplus
}
#endif

#endif