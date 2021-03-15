#include "why_math_functions.h"
#include "why_constants.h"
#include "why_memory_functions.h"

//defined for positive x's and mods
double why_math_modulus(double x, double mod)
{
    double r;
    double result;
    unsigned int integer_part;

    if (mod <= 0 || x < 0)
        return NAN;
    
    if (x > INT_MAX || x < INT_MIN)
        return NAN;

    result = x / mod;
    integer_part = (unsigned int)result;
    r = result - integer_part;

    return r;
}