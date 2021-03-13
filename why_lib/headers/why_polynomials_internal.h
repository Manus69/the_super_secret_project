#ifndef WHY_POLYNOMIALS_INTERNAL_H
#define WHY_POLYNOMIALS_INTERNAL_H

struct p_token *p_token_create(const char *string);

void p_token_reset(struct p_token *token);

#endif