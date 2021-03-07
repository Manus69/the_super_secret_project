#include "why_print_structures.h"
#include "why_print_functions.h"
#include "why_string_buffer_functions.h"
#include "why_string_buffer_structure.h"
#include "why_memory_functions.h"
#include "why_constants.h"
#include "why_string_functions.h"

#include <stdarg.h>
#include <unistd.h>

void token_reset(struct why_printf_token *token)
{
    token->start = token->end;
    token->type = UNKNOWN;

    token->alignment = 1;
    token->precision = PRINTF_PRECISION_DEFAULT;
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

void token_destroy(struct why_printf_token **token)
{
    if (!token || !*token)
        return ;
    
    free(*token);
    *token = NULL;
}

struct why_printf_token *get_plain_text_token(struct why_printf_token *token)
{
    char *current_position;

    current_position = token->start;
    while (*current_position != '\0')
    {
        if (*current_position == PRINTF_SPECIAL_CHAR)
        {
            break ;
        }
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
        token->alignment = 1;

    token->alignment_processed = true;
}

void process_digit(struct why_printf_token *token, char current_char)
{
    if (token->dot_encountered == false)
        token->width = token->width * 10 + current_char - '0';
    else
        token->precision = token->precision * 10 + current_char - '0';
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

int form_argument_string(char *argument_buffer, va_list *arg_list, const struct why_printf_token *token)
{
    int length;

    length = 0;
    if (token->type == D)
        length = why_string_itoa_buffer(va_arg(*arg_list, int), 10, argument_buffer);
    else if (token->type == F)
        length = why_string_ftoa_buffer(va_arg(*arg_list, double), token->precision, argument_buffer);

    return length;
}

int append_literal(why_string_buffer *buffer, va_list *arg_list, struct why_printf_token *token)
{
    char *string;
    int length;
    int delta;

    string = va_arg(*arg_list, char *);
    length = why_string_get_length(string);
    delta = token->width - length;

    why_string_buffer_append_char(buffer, token->padding_char, delta);
    why_string_buffer_append_string(buffer, string);
    length = delta > 0 ? token->width : length;

    return length;
}

int append_to_buffer(why_string_buffer *string_buffer, char *argument_buffer, va_list *arg_list, struct why_printf_token *token)
{
    int length;

    if (token->type == TEXT)
        return why_string_buffer_append_from_string(string_buffer, token->start, token->end - token->start);
    if (token->type == S)
        return append_literal(string_buffer, arg_list, token);

    length = form_argument_string(argument_buffer, arg_list, token);
    why_string_buffer_append_char(string_buffer, token->padding_char, token->width - length);
    why_string_buffer_append_from_string(string_buffer, argument_buffer, length);

    return length;
}

why_string_buffer *why_string_buffer_format_string(const char *format, va_list *arg_list)
{
    why_string_buffer *string_buffer;
    struct why_printf_token *token;
    char argument_buffer[PRINTF_DOUBLE_DBC];

    
    string_buffer = why_string_buffer_create(STRING_BUFFER_DC);
    token = printf_token_create(format);

    while (true)
    {
        token = get_next_token(token);
        if (token->type == BRICKED)
        {
            //error handling?
            break ;
        }
        if (token->eos == true)
            break ;
        append_to_buffer(string_buffer, argument_buffer, arg_list, token);
        token_reset(token);
    }
    
    token_destroy(&token);

    return string_buffer;
}

int why_printf(const char *format, ...)
{
    va_list arg_list;
    why_string_buffer *buffer;
    int length;

    va_start(arg_list, format);
    buffer = why_string_buffer_format_string(format, &arg_list);
    length = write(STDOUT_FILENO, buffer->content, buffer->current - buffer->content);
    va_end(arg_list);
    why_string_buffer_destory(&buffer);

    return length;
}