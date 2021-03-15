#ifndef WHY_POLYNOMIAL_FUNCTIONS_H
#define WHY_POLYNOMIAL_FUNCTIONS_H

#include "why_typedefs.h"

int why_polynomial_get_degree(const why_real_polynomial *p);

double why_polynomial_get_coefficient(const why_real_polynomial *p, int n);

why_real_polynomial *why_polynomial_from_string(const char *string);
void why_polynomial_destroy(why_real_polynomial **p);


#endif