#include <math.h>

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

float64_t fabs(float64_t x)
{
    if (x < 0)
        return -x;

    return x;
}

float64_t ceil(float64_t x)
{
    int32_t n = (int32_t) x;

    if (n >= x)
        return n;

    return n + 1;
}

float64_t exp(float64_t x)
{
    float64_t x0 = fabs(x);

    if (x == 0)
        return 1;

    int32_t k = ceil((x0 / LN_2) - 0.5);
    float64_t p = 1 << k;
    float64_t r = x0 - (k * LN_2);
    float64_t tn = 1;

    for (int32_t i = 14; i > 0; i--)
        tn = tn * (r / i) + 1;

    p *= tn;

    if (x < 0)
        return 1 / p;

    return p;
}

float64_t log(float64_t x)
{
    int32_t yi = y;
    int32_t log2 = 0;
    float64_t x, r;

    while (yi >>= 1)
        log2++;

    x = (float64_t) (1 << log2);
    x = y / x;
    r = -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x;
    r += 0.69314718 * log2;

    return r;
}

float64_t pow(float64_t x, float64_t y)
{
    return exp(x * log(y));
}