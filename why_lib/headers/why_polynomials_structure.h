#ifndef WHY_POLYNOMIALS_STRUCTURE_H
#define WHY_POLYNOMIALS_STRUCTURE_H

#include "why_typedefs.h"

struct why_real_polynomial
{
    why_vector *coefficients;
    int degree;
};

enum p_token_status
{
    GREEN, FOUND, BRICKED, EOS,
};

enum p_string_item
{
    NONE, WS, SIGN, DIGIT, DOT, LETTER, CARET,
};

struct p_token
{
    double decimal;
    double decimal_divisor;
    int sign;
    unsigned int integer;
    unsigned int degree;

    enum p_token_status status;
    enum p_string_item previous_item;

    char *string;

    char variable_symbol;

    char dot_processed;
    char sign_processed;
    char caret_processed;
    char variable_processed;
    char partial_token;
    char coefficient_processed;
};


#endif