#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_vector_functions.h"

why_real_polynomial *why_polynomial_create()
{
    why_real_polynomial *p;

    p = malloc(sizeof(why_real_polynomial));
    if (p)
    {
        p->coefficients = why_vector_create(2, why_memory_copy_double, why_memory_destroy);
        if (!p->coefficients)
        {
            free(p);

            return NULL;
        }
        p->degree = 0;

        return p;
    }

    return NULL;
}

void why_polynomial_destroy(why_real_polynomial **p)
{
    if (!p || !*p)
        return ;
    
    why_vector_destroy(&(*p)->coefficients);
    why_memory_destroy((void **)p);
}

void why_polynomial_get_zeroes(why_real_polynomial *p)
{
    double value;
    int n;

    value = 0;
    n = 0;

    while (n < p->degree)
    {
        why_vector_replace_at(p->coefficients, &value, n);
        n ++;
    }
}

void why_polynomial_set_coefficient(why_real_polynomial *p, int degree, double value)
{
    if (p->degree < degree)
    {
        why_vector_reallocate(p->coefficients, degree - p->degree);
        p->degree = degree;
        why_polynomial_get_zeroes(p);
    }
    why_vector_replace_at(p, &value, degree);
}

//a + bx + cx^2 + ... + qx^n
why_real_polynomial *why_polynomial_from_string(const char *string)
{
    why_real_polynomial *p;

    p = why_polynomial_create();

}