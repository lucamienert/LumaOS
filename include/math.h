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
#define LN_2 0.6931471805599453

#ifdef __cplusplus
extern "C" {
#endif

float64_t abs(float64_t x);
float64_t sin(float64_t x);
float64_t cos(float64_t x);
float64_t fabs(float64_t x);
float64_t ceil(float64_t x);
float64_t exp(float64_t x);
float64_t log(float64_t x);
float64_t pow(float64_t x, float64_t y);

#ifdef __cplusplus
}
#endif

#endif