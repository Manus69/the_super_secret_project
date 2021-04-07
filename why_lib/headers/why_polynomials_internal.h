#ifndef WHY_POLYNOMIALS_INTERNAL_H
#define WHY_POLYNOMIALS_INTERNAL_H

#define DEFAULT_VARIABLE_SYMBOL 'x'

struct p_token *p_token_create(const char *string);

int p_token_next(struct p_token *token);

void p_token_reset(struct p_token *token);

#endif