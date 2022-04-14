#pragma once

#include "inttypes.h"

int64 strlen(const char *str);
void strappchr(const char *str, char c);
int8 strcmp(const char *str1, const char *str2);
char *strcpy(char *target, char *source);
int8 strback(char *str);
void inttostr(int n, char *str);
void strrev(char *str);