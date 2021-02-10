#include "why_lib.h"
#include "why_print.h"
#include "why_matcher.h"

#include <stdarg.h>


#include "why_display.h"
why_vector *parse_format_string(const char *format_string)
{
    why_vector *vector;
    why_string_token *token;
    why_matcher *matcher;
    char *substring;

    vector = why_vector_create(0, NULL, NULL);

    matcher = why_matcher_create(format_string);

    while (true)
    {
        ;
    }

    return vector;
}

char *why_string_get_formatted_string(const char *format, ...)
{
    va_list arg_list;
    why_vector *tokens;
    char *string;


    va_start(arg_list, format);
    string = NULL;
    // tokens = why_string_split(format, '%');
    tokens = parse_format_string(format);
    //
    why_display_vector(tokens, why_display_string);
    //

    va_end(arg_list);

    why_vector_destroy(&tokens);
    return string;
}

int why_print(const char *format, ... )
{
    ;
}

