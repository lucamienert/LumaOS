#include "../include/libc/math.h"

float64 abs(float64 x) {
    return x < 0.0 ? -x : x;
}

float64 sin(float64 x) {
    float64 result;
    asm("fsin" : "=t"(result) : "0"(x));
    return result;
}

float64 cos(float64 x) {
    return sin(x + PI / 2.0);
}