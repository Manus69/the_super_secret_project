#ifndef WHY_POLYNOMIALS_INTERNAL_H
#define WHY_POLYNOMIALS_INTERNAL_H

#include "why_calculus.h"
#include "why_polynomials_structure.h"

#define DEFAULT_VARIABLE_SYMBOL 'x'

struct p_token *p_token_create(const char *string);

int p_token_next(struct p_token *token);

void p_token_reset(struct p_token *token);

enum critical_point classify_critical_point(const why_real_polynomial *p, double x, double f_x);
enum critical_point classify_critical_point_mk2(const why_real_polynomial *p, double x);

#endif