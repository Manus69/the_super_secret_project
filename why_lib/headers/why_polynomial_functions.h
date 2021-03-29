#ifndef WHY_POLYNOMIAL_FUNCTIONS_H
#define WHY_POLYNOMIAL_FUNCTIONS_H

#include "why_typedefs.h"

int why_polynomial_get_degree(const why_real_polynomial *p);

double why_polynomial_get_coefficient(const why_real_polynomial *p, int n);
double why_polynomial_evaluate(const why_real_polynomial *p, double x);

why_real_polynomial *why_polynomial_from_string(const char *string);
why_real_polynomial *why_polynomial_get_derivative(const why_real_polynomial *p);
void why_polynomial_destroy(why_real_polynomial **p);

// why_vector *no_roots();
why_vector *solve_first_degree_equation(const why_real_polynomial *p);
why_vector *solve_second_degree_equation(const why_real_polynomial *p);
why_vector *why_polynomial_get_roots(const why_real_polynomial *p);

#endif