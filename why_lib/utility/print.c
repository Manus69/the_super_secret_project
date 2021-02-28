#include "why_lib.h"
#include "why_print.h"
#include "why_matcher.h"
#include "why_string_buffer.h"

#include <stdarg.h>
#include <unistd.h>

enum state
{
    INSIDE = 1, OUTSIDE,
};

why_string_token *string_token_create(const char *string, int length)
{
    why_string_token *token;

    token = malloc(sizeof(why_string_token));
    token->string = (char *)string;
    token->type = BRICKED;

    token->string_length = length;
    token->actual_length = length;

    token->alignment = -1;
    token->precision = 0;
    token->width = 0;

    return token;
}

int string_token_determine(why_string_token *token)
{
    char *current_position;
    // char *specifier_position;


    if (token->type == TEXT || token->type == PERCENT_SYMBOL)
        return token->type;
    
    current_position = token->string;
    // specifier_position = token->string + token->length - 1;

    if (*current_position == '-')
    {
        token->alignment = -1;
        current_position ++;
    }
    while (why_string_is_digit(*current_position))
    {
        token->width = token->width * 10 + *current_position - '0';
        current_position ++;
    }
    if (*current_position == '.')
    {
        current_position ++;
    }
    while (why_string_is_digit(*current_position))
    {
        token->precision = token->precision * 10 + *current_position - '0';
        current_position ++;
    }

    return token->type;
}

int string_token_classify(why_string_token *token)
{
    char first_char;
    char last_char;

    if (token->string_length == 0)
        return BRICKED;

    first_char = *token->string;
    last_char = token->string[token->string_length - 1];

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
    }
    else
        token->type = TEXT;

    token->type = string_token_determine(token);

    return token->type;
}

//returns a bricked token if there is one
why_string_token *find_bricked_token(why_vector *vector)
{
    why_string_token *bricked_token;


    bricked_token = why_vector_apply_function_mk2(vector, string_token_classify, BRICKED);

    return bricked_token;
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


int why_string_buffer_write_int(why_string_buffer *buffer, why_string_token *token, int number)
{
    int length;

    if (why_string_buffer_check_capacity(buffer, INT_BUFFER_SIZE) == FAILURE)
        return FAILURE;

    length = why_string_itoa_buffer(number, 10, buffer->current);
    buffer->current += length;

    return length;
}

int why_string_buffer_write_double(why_string_buffer *buffer, double x)
{
    int length;

    if (why_string_buffer_check_capacity(buffer, INT_BUFFER_SIZE) == FAILURE)
        return FAILURE;

}

char *why_string_get_formatted_string(const char *format, va_list *arg_list)
{
    why_vector *tokens;
    why_string_token *token;
    why_string_buffer *string_buffer;
    char *string;

    string_buffer = why_string_buffer_create(DEFAULT);
    tokens = get_string_tokens(format);
    token = find_bricked_token(tokens);

    if (token)
    {
        //do something with the bricked token?
        // printf("malformed token: %s\n", token->string);
        why_vector_destroy(&tokens);
    }

    //
    // why_display_vector(tokens, why_display_string_token);
    //

    int n;
    n = 0;

    while (n < why_vector_get_length(tokens))
    {
        token = why_vector_at(tokens, n);
        if (token->type == TEXT)
        {
            why_string_buffer_write_string(string_buffer, token->string);
        }
        if (token->type == D)
            why_string_buffer_write_int(string_buffer, token, va_arg(*arg_list, int));
        
        n ++;
    }

    string = why_string_buffer_get_content(string_buffer);

    why_vector_destroy(&tokens);
    free(string_buffer);

    return string;
}

int why_print(const char *format, ... )
{
    char *string;
    va_list arg_list;
    int length;

    va_start(arg_list, format);
    string = why_string_get_formatted_string(format, &arg_list);
    length = why_string_get_length(string);
    write(STDOUT_FILENO, string, length);

    va_end(arg_list);
    free(string);

    return length;
}

