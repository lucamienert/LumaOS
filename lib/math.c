#include "include/math.h"

float64_t abs(float64_t x) {
    return x < 0.0 ? -x : x;
}

float64_t sin(float64_t x) {
    float64_t result;
    asm("fsin" : "=t"(result) : "0"(x));
    return result;
}

float64_t cos(float64_t x) {
    return sin(x + PI / 2.0);
}