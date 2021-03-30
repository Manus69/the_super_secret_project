#include "why_printf_structures.h"
#include "why_memory_functions.h"
#include "why_constants.h"
#include "why_printf_internal.h"

void token_reset(struct why_printf_token *token)
{
    token->start = token->end;
    token->type = UNKNOWN;

    token->alignment = 1;
    token->precision = 0;
    token->width = 0;

    token->width_processed = false;
    token->alignment_processed = false;
    token->precision_processed = false;
    token->dot_encountered = false;
}

struct why_printf_token *printf_token_create(const char *string)
{
    struct why_printf_token *token;

    if (!string)
        return NULL;

    token = malloc(sizeof(struct why_printf_token));
    if (!token)
        return NULL;
    
    token->start = (char *)string;
    token->end = (char *)string;

    token->padding_char = ' ';
    token->eos = false;

    token_reset(token);

    return token;
}

struct why_printf_token printf_token_create_on_stack(const char *string)
{
    struct why_printf_token token;

    token.start = (char *)string;
    token.end = (char *)string;

    token.padding_char = ' ';
    token.eos = false;

    token_reset(&token);

    return token;
}

void token_destroy(struct why_printf_token **token)
{
    if (!token || !*token)
        return ;
    
    free(*token);
    *token = NULL;
}