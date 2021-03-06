#include "why_print_structures.h"
#include "why_print_functions.h"
#include "why_string_buffer_functions.h"

#include <stdarg.h>

struct why_printf_token *printf_token_create(const why_string_buffer *buffer)
{
    ;
}

void token_destroy(struct why_printf_token **token)
{
    ;
}

void token_reset(struct why_printf_token *token)
{
    ;
}

enum token_type token_classify(struct why_printf_token *token)
{
    ;
}

int form_argument_string(why_string_buffer *argument_buffer, va_list *arg_list, const struct why_printf_token *token)
{
    ;
}

int append_to_buffer(why_string_buffer *string_buffer, why_string_buffer *argument_buffer, const struct why_printf_token *token)
{
    ;
}