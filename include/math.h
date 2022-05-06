#ifndef LUMAOS_MATH_H_
#define LUMAOS_MATH_H_

#pragma once

#include <stdfloat.h>

#define MIN(a, b) \
    a < b ? a : b

#define MAX(a, b) \
    a > b ? a : b

#define LESSTHAN_PREDICATE(a, b) \
    a < b ? 1 : 0

#define E 2.71828
#define PI 3.14159265358979323846264338327950

float64_t abs(float64_t x);
float64_t sin(float64_t x);
float64_t cos(float64_t x);

#endif