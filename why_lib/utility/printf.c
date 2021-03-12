#include "why_printf_structures.h"
#include "why_printf_functions.h"
#include "why_string_buffer_functions.h"
#include "why_string_buffer_structure.h"
#include "why_memory_functions.h"
#include "why_constants.h"
#include "why_printf_constants.h"
#include "why_string_functions.h"
#include "why_printf_internal.h"

#include <stdarg.h>

int form_argument_string(char *argument_buffer, va_list *arg_list, const struct why_printf_token *token)
{
    int length;
    int actual_precision;

    length = 0;
    if (token->type == D)
        length = why_string_itoa_buffer(va_arg(*arg_list, int), 10, argument_buffer);
    else if (token->type == F)
    {
        actual_precision = token->precision_processed ? token->precision : PRINTF_PRECISION_DEFAULT;

        length = why_string_ftoa_buffer((double)va_arg(*arg_list, double), actual_precision, argument_buffer);
    }
    else if (token->type == X)
    {
        length += why_string_uitoa_buffer(va_arg(*arg_list, unsigned int), 16, argument_buffer);
    }
    else if (token->type == P)
    {
        why_memory_copy(argument_buffer, "0x", 2);
        argument_buffer += 2;
        length = 2;
        length += why_string_ultoa_buffer(va_arg(*arg_list, unsigned long), 16, argument_buffer);
    }

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

    if (token->alignment = 1)
    {
        why_string_buffer_append_char(buffer, token->padding_char, delta);
        why_string_buffer_append_string(buffer, string);
    }
    else
    {
        why_string_buffer_append_string(buffer, string);
        why_string_buffer_append_char(buffer, token->padding_char, delta);
    }
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
    if (token->type == PERCENT_SYMBOL)
        return why_string_buffer_append_char(string_buffer, PRINTF_SPECIAL_CHAR, 1);

    length = form_argument_string(argument_buffer, arg_list, token);
    if (token->alignment == 1)
    {
        why_string_buffer_append_char(string_buffer, token->padding_char, token->width - length);
        why_string_buffer_append_from_string(string_buffer, argument_buffer, length);
    }
    else
    {
        why_string_buffer_append_from_string(string_buffer, argument_buffer, length);
        why_string_buffer_append_char(string_buffer, token->padding_char, token->width - length);
    }

    return length;
}

why_string_buffer *why_string_buffer_create_formatted(const char *format, va_list *arg_list)
{
    why_string_buffer *string_buffer;
    struct why_printf_token *token;
    char argument_buffer[PRINTF_DOUBLE_DBC];

    
    string_buffer = why_string_buffer_create(STRING_BUFFER_DC);
    token = printf_token_create(format);
    // why_memory_set(argument_buffer, 0, PRINTF_DOUBLE_DBC);

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
