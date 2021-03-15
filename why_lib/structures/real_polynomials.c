#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_vector_functions.h"
#include "why_polynomials_internal.h"
#include "why_constants.h"
#include "why_polynomial_functions.h"

void why_polynomial_get_zeroes(why_real_polynomial *p)
{
    double value;
    int n;
    int length;

    value = 0;
    n = 0;
    length = why_vector_get_length(p->coefficients);

    while (n < length)
    {
        why_vector_replace_at(p->coefficients, &value, n);
        n ++;
    }
}

why_real_polynomial *why_polynomial_create()
{
    why_real_polynomial *p;
    int length;
    double value;

    p = malloc(sizeof(why_real_polynomial));
    if (p)
    {
        length = 3;
        p->coefficients = why_vector_create(length, why_memory_copy_double, why_memory_destroy);
        if (!p->coefficients)
        {
            free(p);

            return NULL;
        }
        // why_polynomial_get_zeroes(p);
        value = 0;
        while (length)
        {
            why_vector_push(p->coefficients, &value);
            length --;
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

int why_polynomial_get_degree(const why_real_polynomial *p)
{
    return p->degree;
}

double why_polynomial_get_coefficient(const why_real_polynomial *p, int n)
{
    double coefficient;

    coefficient = *(double *)why_vector_at(p->coefficients, n);

    return coefficient;
}

int why_polynomial_reallocate(why_real_polynomial *p, int extra_capacity)
{
    int current_length;
    int n;
    double value;

    if (extra_capacity <= 0)
        return FAILURE;

    current_length = why_vector_get_length(p->coefficients);
    value = 0;

    if (why_vector_reallocate(p->coefficients, extra_capacity) == FAILURE)
        return FAILURE;

    while (extra_capacity)
    {
        why_vector_push(p->coefficients, &value);
        extra_capacity --;
    }
    
    return SUCCESS;
}

int why_polynomial_set_coefficient(why_real_polynomial *p, int degree, double value)
{
    int current_length;

    current_length = why_vector_get_length(p->coefficients);
    if (degree >= current_length)
    {
        if (why_polynomial_reallocate(p, degree - current_length + 1) == FAILURE)
            return FAILURE;
    }
    why_vector_replace_at(p->coefficients, &value, degree);
    if (degree > p->degree)
        p->degree = degree;

    return SUCCESS;
}

static int adjust_coefficient(why_real_polynomial *p, const struct p_token *token)
{
    double old_coefficient;
    double new_coefficient;
    int current_length;

    current_length = why_vector_get_length(p->coefficients);
    if (token->degree >= current_length)
    {
        if (why_polynomial_reallocate(p, token->degree - current_length + 1) == FAILURE)
            return FAILURE;
    }

    new_coefficient = (token->integer + token->decimal) * token->sign;
    old_coefficient = why_polynomial_get_coefficient(p, token->degree);
    why_polynomial_set_coefficient(p, token->degree, new_coefficient + old_coefficient);

    return SUCCESS;
}

//a + bx + cx^2 + ... + qx^n
why_real_polynomial *why_polynomial_from_string(const char *string)
{
    why_real_polynomial *p;
    struct p_token *token;
    double coefficient;
    double old_coefficient;

    token = p_token_create(string);
    p = why_polynomial_create();

    while (true)
    {
        p_token_next(token);

        if (token->status == FOUND)
        {
            adjust_coefficient(p, token);
        }
        else if (token->status == EOS && (token->partial_token || token->empty_token))
        {
            adjust_coefficient(p, token);
            free(token);
            
            return p;
        }
        else
        {
            //handle errors;
            free(token);
            why_polynomial_destroy(&p);
            
            return NULL;
        }
        p_token_reset(token);
    }
}

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