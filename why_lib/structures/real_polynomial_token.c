#include "why_polynomials_structure.h"
#include "why_memory_functions.h"
#include "why_constants.h"
#include "why_polynomials_internal.h"
#include "why_string_functions.h"

void p_token_reset(struct p_token *token)
{
    token->decimal = 0;
    token->decimal_divisor = 10.0;
    token->degree = 0;
    token->integer = 0;
    token->sign = 1;

    token->previous_item = NONE;
    token->status = GREEN;
    token->variable_symbol = 'x';

    token->caret_processed = false;
    token->coefficient_processed = false;
    token->dot_processed = false;
    token->empty_token = true;
    token->partial_token = false;
    token->sign_processed = false;
    token->variable_processed = false;
}

struct p_token *p_token_create(const char *string)
{
    struct p_token *token;

    token = malloc(sizeof(struct p_token));
    if (!token)
        return NULL;
    
    token->string = (char *)string;
    p_token_reset(token);

    return token;
}

int p_token_skip(struct p_token *token)
{
    while (why_string_is_whitespace(*token->string))
        token->string ++;
    if (*token->string == '\0')
        token->status = EOS;
    
    token->previous_item = WS;

    return token->status;
}

int p_token_brick(struct p_token *token)
{
    token->status = BRICKED;

    return token->status;
}

int p_token_process_whitespace(struct p_token *token)
{
    enum p_string_item previous;

    previous = token->previous_item;
    if (previous == DOT || previous == CARET)
        return p_token_brick(token);

    if (previous == DIGIT || token->caret_processed)
        token->status = FOUND;

    token->previous_item = WS;

    return token->status;
}

int p_token_process_sign(struct p_token *token)
{
    if (token->sign_processed || token->previous_item == DOT || token->previous_item == CARET)
        return p_token_brick(token);

    token->empty_token = false;
    if (token->previous_item == DIGIT || token->previous_item == LETTER || token->previous_item == WS)
    {
        token->status = FOUND;

        return token->status;
    }

    if (*token->string == '-')
        token->sign = -1;

    token->previous_item = SIGN;

    return token->status;
}

int p_token_process_digit(struct p_token *token)
{
    if (token->previous_item == LETTER)
        return p_token_brick(token);

    if (token->caret_processed == true)
    {
        token->degree = token->degree * 10 + (*token->string - '0');
    }
    else if (token->dot_processed == false)
    {
        token->integer = token->integer * 10 + (*token->string - '0');
    }
    else
    {
        token->decimal += (*token->string - '0') / token->decimal_divisor;
        token->decimal_divisor = token->decimal_divisor / 10;
    }
    token->previous_item = DIGIT;
    token->partial_token = true;
    token->empty_token = false;

    return token->status;
}

int p_token_process_dot(struct p_token *token)
{
    if (token->dot_processed)
        return p_token_brick(token);
    if (token->previous_item != DIGIT)
        return p_token_brick(token);
    
    token->previous_item = DOT;
    token->empty_token = false;

    return token->status;
}

int p_token_process_letter(struct p_token *token)
{
    if (token->previous_item == CARET || token->previous_item == DOT)
        return p_token_brick(token);
    if (token->previous_item == DIGIT)
        token->coefficient_processed = true;

    if (token->variable_processed == false)
    {
        token->variable_symbol = *token->string;
        token->variable_processed = true;
    }
    else if (*token->string != token->variable_symbol)
        return p_token_brick(token);

    if (token->previous_item != DIGIT)
    {
        token->integer = 1;
        token->degree = 1;
    }

    token->previous_item = LETTER;
    token->partial_token = true;
    token->empty_token = false;

    return token->status;
}

int p_token_process_caret(struct p_token *token)
{
    if (token->previous_item != LETTER)
        return p_token_brick(token);

    token->previous_item = CARET;
    token->caret_processed = true;
    token->variable_processed = true;
    token->empty_token = false;

    token->degree = 0;

    return token->status;
}

int p_token_process_nul(struct p_token *token)
{
    if (token->previous_item == CARET || token->previous_item == DOT)
        return p_token_brick(token);

    if (token->partial_token || token->empty_token)
        token->status = EOS;
    else
        return p_token_brick(token);

    return token->status;
}

int p_token_next(struct p_token *token)
{
    char current_char;

    while (true)
    {
        current_char = *token->string;
        if (why_string_is_whitespace(current_char))
            p_token_process_whitespace(token);
        else if (current_char == '+' || current_char == '-')
            p_token_process_sign(token);
        else if (why_string_is_digit(current_char))
            p_token_process_digit(token);
        else if (why_string_is_letter(current_char))
            p_token_process_letter(token);
        else if (current_char == '^')
            p_token_process_caret(token);
        else if (current_char == '\0')
            p_token_process_nul(token);
        
        if (token->status == BRICKED || token->status == FOUND || token->status == EOS)
            return token->status;
            
        token->string ++;
    }
}