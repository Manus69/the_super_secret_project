#ifndef WHY_POLYNOMIALS_INTERNAL_H
#define WHY_POLYNOMIALS_INTERNAL_H

struct polynomial_token *p_token_create(const char *string);

void p_token_reset(struct polynomial_token *token);

#endif