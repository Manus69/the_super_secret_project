#ifndef WHY_POLYNOMIALS_STRUCTURE_H
#define WHY_POLYNOMIALS_STRUCTURE_H

#include "why_typedefs.h"

struct why_real_polynomial
{
    why_vector *coefficients;
    int degree;
};

enum polynomial_token_status
{
    GREEN, BRICKED, EOS,
};

struct polynomial_token
{
    double decimal;
    int sign;
    unsigned int integer;
    unsigned int degree;

    enum polynomial_token_status status;

    char *string;

    char dot_processed;
    char sign_processed;
    char variable_processed;
};


#endif