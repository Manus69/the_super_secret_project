#include "why_printf_internal.h"
#include "why_printf_constants.h"
#include "why_printf_functions.h"
#include "why_printf_structures.h"
#include "why_constants.h"
#include "why_string_functions.h"

struct why_printf_token *get_plain_text_token(struct why_printf_token *token)
{
    char *current_position;

    current_position = token->start;
    while (*current_position != '\0')
    {
        if (*current_position == PRINTF_SPECIAL_CHAR)
            break ;
        current_position ++;
    }

    if (current_position - token->start)
    {
        token->end = current_position;
        token->type = TEXT;

        return token;
    }
    token->eos = true;

    return token;
}

struct why_printf_token *process_special_char(struct why_printf_token *token, char *current_position)
{
    if (current_position - token->start == 1)
        token->type = PERCENT_SYMBOL;
    else
        token->type = BRICKED;
    
    current_position ++;
    token->end = current_position;

    return token;
}

void process_plus_minus(struct why_printf_token *token, char current_char)
{
    if (token->alignment_processed == true)
        token->type = BRICKED;

    if (current_char == '-')
        token->alignment = -1;
    else if (current_char == '+')
    {
        ; // token->alignment = 1; //implement this shit later?
    }

    token->alignment_processed = true;
}

void process_digit(struct why_printf_token *token, char current_char)
{
    if (token->dot_encountered == false)
    {
        token->width = token->width * 10 + current_char - '0';
        token->width_processed = true;
    }
    else
    {
        token->precision = token->precision * 10 + current_char - '0';
        token->precision_processed = true;
    }
}

void process_dot(struct why_printf_token *token)
{
    if (token->dot_encountered == false)
        token->dot_encountered = true;
    else
        token->type = BRICKED;
}

struct why_printf_token *process_specifier(struct why_printf_token *token, char *current_position)
{
    if (*current_position == PRINTF_SPECIFIERS[D])
        token->type = D;
    else if (*current_position == PRINTF_SPECIFIERS[F])
        token->type = F;
    else if (*current_position == PRINTF_SPECIFIERS[S])
        token->type = S;
    else if (*current_position == PRINTF_SPECIFIERS[P])
        token->type = P;
    else if (*current_position == PRINTF_SPECIFIERS[X])
        token->type = X;
    else
        token->type = BRICKED;
    
    current_position ++;
    token->end = current_position;

    return token;
}

struct why_printf_token *get_next_token(struct why_printf_token *token)
{
    char *current_position;

    current_position = token->start;
    
    if (*current_position != PRINTF_SPECIAL_CHAR)
        return get_plain_text_token(token);
    
    current_position ++;
    while (*current_position != '\0')
    {
        if (*current_position == PRINTF_SPECIAL_CHAR)
            return process_special_char(token, current_position);
        else if (*current_position == '-' || *current_position == '+')
            process_plus_minus(token, *current_position);
        else if (why_string_is_digit(*current_position))
            process_digit(token, *current_position);
        else if (*current_position == '.')
            process_dot(token);
        else if (why_string_get_index_of(PRINTF_SPECIFIERS, *current_position) != -1)
            return process_specifier(token, current_position);

        current_position ++;
    }
    token->type = BRICKED;

    return token;
}