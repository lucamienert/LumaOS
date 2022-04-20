#include "../include/utils/math.h"

float64 sin2(float64 x) {
    float64 result;
    asm("fsin" : "=t"(result) : "0"(x));
    return result;
}

float64 cos2(float64 x) {
    return sin2(x + PI / 2.0);
}