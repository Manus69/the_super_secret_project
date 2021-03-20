#ifndef WHY_MATH_H
#define WHY_MATH_H

#include "why_polynomial_functions.h"

unsigned int why_math_random(unsigned int seed, unsigned int max);
unsigned int why_math_get_next_prime(unsigned int number);

int why_math_is_prime(unsigned int number);

double why_math_sqrt(double x);
double why_math_modulus(double x, double mod);
double why_math_sin(double phi);
double why_math_cos(double phi);

#endif