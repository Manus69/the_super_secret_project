#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_constants.h"
#include "why_polynomials_internal.h"
#include "why_string_functions.h"


double why_polynomial_evaluate(const why_real_polynomial *p, double x)
{
    double value;
    int n;

    value = why_polynomial_get_coefficient(p, p->degree);
    n = p->degree - 1;
    while (n >= 0)
    {
        value = value * x + why_polynomial_get_coefficient(p, n);
        n --;
    }

    return value;
}

why_real_polynomial *why_polynomial_add(const why_real_polynomial *p, const why_real_polynomial *q)
{
    why_real_polynomial *result;

    return result;
}

why_real_polynomial *why_polynomial_multiply(const why_real_polynomial *p, const why_real_polynomial *q)
{
    why_real_polynomial *result;

    return result;
}

// f(x) = a + bx + cx^2 + dx^3 + ... + kx^n
// f'(x) = b + 2cx + 3dx^2 + ... + nkx^(n-1)

why_real_polynomial *why_polynomial_get_derivative(const why_real_polynomial *p)
{
    why_real_polynomial *derivative;
    int n;
    double coefficient;

    derivative = why_polynomial_create(p->degree);
    n = 0;

    while (n < p->degree)
    {
        coefficient = (n + 1) * why_polynomial_get_coefficient(p, n + 1);
        why_polynomial_set_coefficient(derivative, n, coefficient);
        n ++;
    }

    return derivative;
}