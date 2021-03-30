#ifndef WHY_PRINTF_INTERNAL_H
#define WHY_PRINTF_INTERNAL_H

#include "why_printf_structures.h"
#include "why_typedefs.h"

#include <stdarg.h>

void token_reset(struct why_printf_token *token);
struct why_printf_token *printf_token_create(const char *string);
struct why_printf_token printf_token_create_on_stack(const char *string);
void token_destroy(struct why_printf_token **token);
void why_string_buffer_format_args(why_string_buffer *string_buffer, const char *format, va_list *arg_list);

struct why_printf_token *get_next_token(struct why_printf_token *token);

why_string_buffer *why_string_buffer_create_formatted(const char *format, va_list *arg_list);

#endif