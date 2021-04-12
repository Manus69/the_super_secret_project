#ifndef WHY_POLYNOMIAL_FUNCTIONS_H
#define WHY_POLYNOMIAL_FUNCTIONS_H

#include "why_typedefs.h"

int why_polynomial_get_degree(const why_real_polynomial *p);
int why_polynomial_set_coefficient(why_real_polynomial *p, int degree, double value);

double why_polynomial_get_coefficient(const why_real_polynomial *p, int n);
double why_polynomial_increment_coefficient(why_real_polynomial *p, int degree, double value);
double why_polynomial_evaluate(const why_real_polynomial *p, double x);
double why_polynomial_newtons_method(const why_real_polynomial *p, double x_initial);
double why_polynomial_get_root_bisection(const why_real_polynomial *p, double left, double right);

why_real_polynomial *why_polynomial_from_string(const char *string);
why_real_polynomial *why_polynomial_create(int size);
why_real_polynomial *why_polynomial_get_derivative(const why_real_polynomial *p);
why_real_polynomial *why_polynomial_add(const why_real_polynomial *p, const why_real_polynomial *q);
why_real_polynomial *why_polynomial_multiply(const why_real_polynomial *p, const why_real_polynomial *q);

void why_polynomial_add_to(why_real_polynomial * p, const why_real_polynomial *q);
void why_polynomial_destroy(why_real_polynomial **p);

why_vector *no_roots();
why_vector *solve_first_degree_equation(const why_real_polynomial *p);
why_vector *solve_second_degree_equation(const why_real_polynomial *p);
why_vector *why_polynomial_get_roots(const why_real_polynomial *p);

#endif