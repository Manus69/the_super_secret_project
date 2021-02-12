#include "why_lib.h"
#include "why_print.h"
#include "why_matcher.h"

#include <stdarg.h>


enum state
{
    INSIDE = 1, OUTSIDE,
};

why_string_token *string_token_create(const char *string, int length)
{
    why_string_token *token;

    token = malloc(sizeof(why_string_token));
    token->string = (char *)string;
    token->type = BROKEN;
    token->length = length;

    token->alignment = 0;
    token->precision = 0;
    token->width = 0;

    return token;
}

enum token_type string_token_classify(why_string_token *token)
{
    char first_char;
    char last_char;

    if (token->length == 0)
        return BROKEN;

    first_char = *token->string;
    last_char = token->string[token->length - 1];

    if (first_char == SPECIAL_CHAR)
    {
        if (last_char == SPECIAL_CHAR)
            token->type = PERCENT_SYMBOL;
        else if (last_char == SPECIFIERS[D])
            token->type = D;
        else if (last_char == SPECIFIERS[F])
            token->type = F;
        else if (last_char == SPECIFIERS[S])
            token->type = S;
        else if (last_char == SPECIFIERS[P])
            token->type = P;
        
        return token->type;
    }

    token->type = TEXT;

    return token->type;
}

//returns a bricked token if there is one
why_string_token *classify_all_tokens(why_vector *vector)
{
    ;
}

void string_token_destroy(why_string_token **token)
{
    free((*token)->string);
    why_memory_destroy((void **)token);
}

static void form_token_and_push(const char *format_string, const char *current_position, why_vector *vector)
{
    char *substring;
    why_string_token *token;
    int diff;

    diff = current_position - format_string;
    if (!diff)
        return ;
    
    substring = why_string_create_from_char_array(format_string, 0, diff);
    token = string_token_create(substring, diff);

    why_vector_push(vector, token);
}

#include "why_display.h"
why_vector *get_string_tokens(const char *format_string)
{
    why_vector *vector;
    char *current_position;
    enum state state;

    if (!format_string)
        return NULL;

    vector = why_vector_create(0, NULL, string_token_destroy);

    current_position = (char *)format_string;
    state = OUTSIDE;

    while (*current_position != '\0')
    {
        if (state == OUTSIDE)
        {
            if (*current_position == SPECIAL_CHAR)
            {
                form_token_and_push(format_string, current_position, vector);

                state = INSIDE;
                format_string = current_position;
            }
            current_position ++;
        }
        else
        {
            if (*current_position == SPECIAL_CHAR || why_string_get_index_of(SPECIFIERS, *current_position) != -1)
            {
                form_token_and_push(format_string, current_position + 1, vector);

                state = OUTSIDE;
                current_position ++;
                format_string = current_position;
            }
            else
                current_position ++;
        }
    }

    form_token_and_push(format_string, current_position, vector);

    return vector;
}

char *why_string_get_formatted_string(const char *format, ...)
{
    va_list arg_list;
    why_vector *tokens;
    char *string;


    va_start(arg_list, format);
    string = NULL;
    tokens = get_string_tokens(format);
    //
    why_display_vector(tokens, why_display_string_token);
    //

    va_end(arg_list);

    why_vector_destroy(&tokens);
    return string;
}

int why_print(const char *format, ... )
{
    ;
}

