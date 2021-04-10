#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_vector_functions.h"
#include "why_polynomials_internal.h"
#include "why_constants.h"
#include "why_macros.h"
#include "why_polynomial_functions.h"
#include "why_math_functions.h"

//this is wrong, when p does not have a root or p'(0) == 0
double why_polynomial_newtons_method(const why_real_polynomial *p, double x_initial)
{
    why_real_polynomial *derivative;
    double x;
    double f_value;
    double f_prime_value;

    if (!p)
        return NAN;

    x = x_initial;
    f_value = why_polynomial_evaluate(p, x);
    derivative = why_polynomial_get_derivative(p);

    while (ABS(f_value) > ROOT_EPSILON)
    {
        f_prime_value = why_polynomial_evaluate(derivative, x);
        if (ABS(f_prime_value) < ROOT_EPSILON)
        {
            return NAN;
        }

        x = x - f_value / f_prime_value;
        f_value = why_polynomial_evaluate(p, x);
    }
    why_polynomial_destroy(&derivative);

    return x;
}