#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_vector_functions.h"
#include "why_polynomials_internal.h"
#include "why_constants.h"
#include "why_macros.h"
#include "why_polynomial_functions.h"
#include "why_math_functions.h"

enum critical_point classify_critical_point(const why_real_polynomial *p, double x, double f_x)
{
    double left_value;
    double right_value;

    left_value = why_polynomial_evaluate(p, x - ROOT_DELTA);
    right_value = why_polynomial_evaluate(p, x + ROOT_DELTA);

    if (f_x > 0)
    {
        if (left_value < f_x && right_value < f_x)
            return LOCAL_MAX;
        else if (left_value < f_x && right_value > f_x)
            return INFLECTION_INCREASING;
        else if (left_value > f_x && right_value < f_x)
            return INFLECTION_DECREASING;
        else
            return LOCAL_MIN;
    }
    else if (f_x < 0)
    {
        if (left_value > f_x && right_value > f_x)
            return LOCAL_MIN;
        else if (left_value > f_x && right_value < f_x)
            return INFLECTION_DECREASING;
        else if (left_value < f_x && right_value > f_x)
            return INFLECTION_INCREASING;
        else
            return LOCAL_MAX;
    }
    return BRICKED_POINT;
}

enum critical_point classify_critical_point_mk2(const why_real_polynomial *p, double x)
{
    double f_x;

    f_x = why_polynomial_evaluate(p, x);

    return classify_critical_point(p, x, f_x);
}

//this gets shit on by inflection points
double perturb_value(double x, double f_value, const why_real_polynomial *first_derivative)
{
    why_real_polynomial *second_derivative;
    double f_double_prime_value;
    double new_x;

    second_derivative = why_polynomial_get_derivative(first_derivative);
    f_double_prime_value = why_polynomial_evaluate(second_derivative, x);

    new_x = NAN;

    if (f_double_prime_value < 0) //local max
    {
        if (f_value > 0)
            new_x = x - ROOT_DELTA;
    }
    else if (f_double_prime_value > 0) //local min
    {
        if (f_value < 0)
            new_x = x + ROOT_DELTA;
    }
    //else - compute some higher derivatives

    why_polynomial_destroy(&second_derivative);

    return new_x;
}

static double perturb_value_mk2(double x, double f_value, const why_real_polynomial *p)
{
    double left_value;
    double right_value;

    left_value = why_polynomial_evaluate(p, x - ROOT_DELTA);
    right_value = why_polynomial_evaluate(p, x + ROOT_DELTA);

    if (f_value > 0)
    {
        if (left_value < f_value && right_value < f_value)
            x = x - ROOT_DELTA;
        else if (left_value < f_value && right_value > f_value)
            x = x - ROOT_DELTA;
        else if (left_value > f_value && right_value < f_value)
            x = x + ROOT_DELTA;
        else
            x = NAN;
    }
    else if (f_value < 0)
    {
        if (left_value > f_value && right_value > f_value)
            x = x - ROOT_DELTA;
        else if (left_value > f_value && right_value < f_value)
            x = x - ROOT_DELTA;
        else if (left_value < f_value && right_value > f_value)
            x = x + ROOT_DELTA;
        else
            x = NAN;
    }

    return x;
}

//works locally
double why_polynomial_newtons_method(const why_real_polynomial *p, double x)
{
    why_real_polynomial *first_derivative;
    double f_value;
    double f_prime_value;

    f_value = why_polynomial_evaluate(p, x);
    first_derivative = why_polynomial_get_derivative(p);

    while (ABS(f_value) > ROOT_EPSILON)
    {
        f_prime_value = why_polynomial_evaluate(first_derivative, x);
        if (ABS(f_prime_value) < ROOT_EPSILON)
        {
            x = perturb_value_mk2(x, f_value, p);
            if (x == NAN)
                break ;
            
            f_value = why_polynomial_evaluate(p, x);
            continue ;
        }

        x = x - f_value / f_prime_value;
        f_value = why_polynomial_evaluate(p, x);
    }

    why_polynomial_destroy(&first_derivative);

    return x;
}

//this thing has overflow issues
double why_polynomial_newtons_mk2(const why_real_polynomial *p, double x0)
{
    why_real_polynomial *p_prime;
    double x1;
    double p_x;
    double p_prime_x;

    p_prime = why_polynomial_get_derivative(p);

    while (true)
    {
        p_x = why_polynomial_evaluate(p, x0);
        p_prime_x = why_polynomial_evaluate(p_prime, x0);
        
        if (IS_EQUAL(p_prime_x, 0, ROOT_EPSILON))
            return NAN;

        x1 = x0 - p_x / p_prime_x;

        if (IS_EQUAL(x0, x1, ROOT_DELTA))
            break ;
        
        x0 = x1;
    }

    why_polynomial_destroy(&p_prime);

    return x1;
}