#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_vector_functions.h"
#include "why_polynomials_internal.h"
#include "why_constants.h"
#include "why_macros.h"
#include "why_polynomial_functions.h"
#include "why_math_functions.h"

static int check_root_and_push(why_vector *roots, double root)
{
    if (root != NAN)
    {
        return why_vector_push(roots, &root);
    }

    return FAILURE;
}

why_vector *find_roots_near_critical_point(const why_real_polynomial *p, double critical_point)
{
    why_vector *roots;
    enum critical_point point_type;
    double f_x;
    double root;

    f_x = why_polynomial_evaluate(p, critical_point);
    point_type = classify_critical_point(p, critical_point, f_x);
    roots = no_roots();

    if (point_type == LOCAL_MAX && f_x > 0)
        return roots;
    
    if (point_type == LOCAL_MIN && f_x < 0)
        return roots;
    
    root = why_polynomial_newtons_method(p, critical_point - ROOT_DELTA);
    check_root_and_push(roots, root);

    if (point_type == LOCAL_MIN || point_type == LOCAL_MAX)
    {
        root = why_polynomial_newtons_method(p, critical_point + ROOT_DELTA);
        check_root_and_push(roots, root);
    }
    
    return roots;
}

why_vector *iterate_over_critical_points(const why_real_polynomial *p, why_vector *critical_points)
{
    why_vector *roots;
    why_vector *local_roots;
    double current_point;

    roots = no_roots();
    while (why_vector_get_length(critical_points))
    {
        current_point = *(double *)why_vector_pop(critical_points);
        local_roots = find_roots_near_critical_point(p, current_point);
        why_vector_append_and_destroy(roots, local_roots);
    }

    return roots;
}

why_vector *compute_roots_via_calculus(const why_real_polynomial *p)
{
    why_real_polynomial *first_derivative;
    why_vector *roots;
    why_vector *critical_points;
    double root;

    first_derivative = why_polynomial_get_derivative(p);
    critical_points = why_polynomial_get_roots(first_derivative);

    if (why_vector_get_length(critical_points) == 0)
    {
        roots = no_roots();
        root = why_polynomial_newtons_method(p, 0);
        check_root_and_push(roots, root);
    }
    else
    {
        roots = iterate_over_critical_points(p, critical_points);
    }
    
    why_polynomial_destroy(&first_derivative);
    why_vector_destroy(&critical_points);

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

    return compute_roots_via_calculus(p);
}