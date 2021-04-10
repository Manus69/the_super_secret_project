#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_vector_functions.h"
#include "why_polynomials_internal.h"
#include "why_constants.h"
#include "why_macros.h"
#include "why_polynomial_functions.h"
#include "why_math_functions.h"

static int compare_if_increasing(double middle)
{
    return middle < 0;
}

static int compare_if_decreasing(double middle)
{
    return middle > 0;
}

static double bisect_function(const why_real_polynomial *p, double left, double right, int (*compare)())
{
    double f_middle;
    double middle;

    middle = (right - left) / 2;
    f_middle = why_polynomial_evaluate(p, middle);

    while (ABS(f_middle) > ROOT_EPSILON)
    {
        if (compare(middle))
            left = middle;
        else
            right = middle;
        
        middle = (right - left) / 2;
        f_middle = why_polynomial_evaluate(p, middle);
    }
    
    return middle;
}

//assumes that f(left) has sign different from f(right)
double why_polynomial_get_root_bisection(const why_real_polynomial *p, double left, double right)
{
    double f_left;
    double f_right;
    int increasing;

    f_left = why_polynomial_evaluate(p, left);
    f_right = why_polynomial_evaluate(p, right);
    increasing = false;

    if (f_left * f_right > 0)
        return NAN;

    if (f_left < 0)
        increasing = true;
    
    if (increasing)
        return bisect_function(p, left, right, compare_if_increasing);
    else
        return bisect_function(p, left, right, compare_if_decreasing);
}