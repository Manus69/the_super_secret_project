#include "why_lib.h"

#include <stdarg.h>

#include "why_display.h"
char *why_string_get_formatted_string(const char *format, ...)
{
    va_list arg_list;
    why_vector *tokens;
    char *string;


    va_start(arg_list, format);
    string = NULL;
    tokens = why_string_split(format, '%');

    why_display_vector(tokens, why_display_string);

    va_end(arg_list);

    why_vector_destroy(&tokens);
    return string;
}

int why_print(const char *format, ... )
{
    ;
}

