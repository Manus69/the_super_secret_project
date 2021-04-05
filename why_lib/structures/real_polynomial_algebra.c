#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_constants.h"
#include "why_polynomials_internal.h"
#include "why_polynomial_functions.h"
#include "why_string_functions.h"
#include "why_macros.h"


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

void why_polynomial_add_to(why_real_polynomial * p, const why_real_polynomial *q)
{
    int n;
    double coefficient;

    n = 0;
    while (n <= q->degree)
    {
        coefficient = why_polynomial_get_coefficient(q, n);
        
        why_polynomial_increment_coefficient(p, n, coefficient);
        n ++;
    }
}

//c = SIGMA(k = 0; k = n)( p[k]q[n-k] )
static double get_coefficient(const why_real_polynomial *p, const why_real_polynomial *q, int n)
{
    double a;
    double b;
    double c;
    int k;

    c = 0;
    k = 0;
    while (k <= n)
    {
        a = why_polynomial_get_coefficient(p, k);
        b = why_polynomial_get_coefficient(q, n - k);
        c += a * b;
        k ++;
    }

    return c;
}

//this is slow on high degree polynomials
why_real_polynomial *why_polynomial_multiply(const why_real_polynomial *p, const why_real_polynomial *q)
{
    why_real_polynomial *result;
    double coefficient;
    int degree;
    int n;

    degree = MAX(p->degree, q->degree);
    result = why_polynomial_create(degree + 1);
    n = 0;
    while (n <= degree)
    {
        coefficient = get_coefficient(p, q, n);
        why_polynomial_set_coefficient(result, n, coefficient);
        n ++;
    }

    return result;
}

why_real_polynomial *why_polynomial_add(const why_real_polynomial *p, const why_real_polynomial *q)
{
    why_real_polynomial *result;
    int degree;

    degree = MAX(p->degree, q->degree);
    result = why_polynomial_create(degree + 1);
    why_polynomial_add_to(result, p);
    why_polynomial_add_to(result, q);
    
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