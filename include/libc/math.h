#ifndef LUMAOS_MATH_H_
#define LUMAOS_MATH_H_

#pragma once

#include "stdint.h"

#define MIN(a, b) \
    a < b ? a : b

#define MAX(a, b) \
    a > b ? a : b

#define E 2.71828
#define PI 3.14159265358979323846264338327950

float64 abs(float64 x);
float64 sin(float64 x);
float64 cos(float64 x);

#endif