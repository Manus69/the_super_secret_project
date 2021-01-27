#include "why_lib.h"

#include <stdarg.h>

#define SPECIAL_CHAR '%'
#define SPECIFIERS "dfsp"


#include "why_display.h"
why_vector *parse_format_string(const char *format_string)
{
    why_vector *vector;
    char *token;
    char *current_pointer;
    int length;
    int special_char_encountered;

    vector = why_vector_create(0, NULL, NULL);

    current_pointer = (char *)format_string;
    special_char_encountered = false;

    

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

