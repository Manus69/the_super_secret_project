#include "why_math_functions.h"
#include "why_memory_functions.h"
#include "why_constants.h"
#include "why_macros.h"

double why_math_sqrt(double x)
{
    double left;
    double right;
    double middle;
    double delta;
    double value;

    if (x < 0)
        return NAN;
    
    left = 0;
    right = x;
    middle = (right + left) / 2;
    value = middle * middle;
    delta = value - x;

    while (ABS(delta) > EPSILON)
    {
        if (value > x)
            right = middle;
        else
            left = middle;
        middle = (right + left) / 2;
        value = middle * middle;
        delta = value - x;
    }

    return middle;
}