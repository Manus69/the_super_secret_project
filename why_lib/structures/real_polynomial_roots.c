#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_vector_functions.h"
#include "why_polynomials_internal.h"
#include "why_constants.h"
#include "why_polynomial_functions.h"
#include "why_math_functions.h"

inline why_vector *no_roots()
{
    return why_vector_create(1, why_memory_copy_double, why_memory_destroy);
}

why_vector *solve_first_degree_equation(const why_real_polynomial *p)
{
    double c0;
    double c1;
    double root;
    why_vector *roots;

    c0 = why_polynomial_get_coefficient(p, 0);
    c1 = why_polynomial_get_coefficient(p, 1);

    if (c1 == 0 && c0 != 0)
        return no_roots();
    
    roots = no_roots();
    root = -1 * c0 / c1;
    why_vector_push(roots, &root);

    return roots;
}

why_vector *solve_second_degree_equation(const why_real_polynomial *p)
{
    double a; //make one array of doubles for this
    double b;
    double c;
    double discriminant;
    double root;
    why_vector *roots;

    a = why_polynomial_get_coefficient(p, 2);
    b = why_polynomial_get_coefficient(p, 1);
    c = why_polynomial_get_coefficient(p, 0);

    if (a == 0)
        return solve_first_degree_equation(p);

    roots = no_roots();
    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return roots;
    
    root = (- b + why_math_sqrt(discriminant)) / (2 * a);
    why_vector_push(roots, &root);

    if (discriminant > 0)
    {
        root = (-b - why_math_sqrt(discriminant)) / (2 * a);
        why_vector_push(roots, &root);
    }

    return roots;
}

why_vector *why_polynomial_get_roots(const why_real_polynomial *p)
{
    if (p->degree == 0)
        return no_roots();
    if (p->degree == 1)
        return solve_first_degree_equation(p);
    if (p->degree == 2)
        return solve_second_degree_equation(p);
}