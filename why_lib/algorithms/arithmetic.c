#include "why_math_functions.h"
#include "why_constants.h"
#include "why_memory_functions.h"
#include "why_macros.h"

double why_math_modulus(double x, double mod)
{
    double r;
    double result;
    int integer_part;

    if (mod <= 0)
        return NAN;
    
    if (x > INT_MAX || x < INT_MIN)
        return NAN;

    result = x / mod;
    integer_part = (int)result;
    if (x >= 0)
    {
        r = (result - integer_part) * mod;
    }
    else
    {
        r = (result - integer_part + 1) * mod;
    }

    return r;
}

int why_math_is_equal(double a, double b, double epsilon)
{
    return (ABS(a - b) < epsilon);
}