#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_constants.h"
#include "why_polynomials_internal.h"

void p_token_reset(struct polynomial_token *token)
{
    token->decimal = 0;
    token->degree = 0;
    token->dot_processed = false;
    token->integer = 0;
    token->sign = 1;
    token->sign_processed = false;
    token->status = GREEN;
    token->variable_processed = false;
}

struct polynomial_token *p_token_create(const char *string)
{
    struct polynomial_token *token;

    token = malloc(sizeof(struct polynomial_token));
    if (!token)
        return NULL;
    
    token->string = (char *)string;
    p_token_reset(token);

    return token;
    
}