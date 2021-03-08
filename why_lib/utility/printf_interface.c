#include "why_printf_structures.h"
#include "why_printf_functions.h"
#include "why_string_buffer_functions.h"
#include "why_string_buffer_structure.h"
#include "why_constants.h"
#include "why_printf_constants.h"
#include "why_printf_internal.h"
#include "why_memory_functions.h"

#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

int why_printf(const char *format, ...)
{
    va_list arg_list;
    why_string_buffer *buffer;
    int length;

    va_start(arg_list, format);
    buffer = why_string_buffer_create_formatted(format, &arg_list);
    length = write(STDOUT_FILENO, buffer->content, buffer->current - buffer->content);

    va_end(arg_list);
    why_string_buffer_destory(&buffer);

    return length;
}

char *why_sprintf(const char *format, ...)
{
    va_list arg_list;
    why_string_buffer *buffer;
    char *string;
    
    va_start(arg_list, format);
    buffer = why_string_buffer_create_formatted(format, &arg_list);
    string = buffer->content;
    string[buffer->current - buffer->content] = '\0';

    va_end(arg_list);
    free(buffer);

    return string;
}

int why_fprintf(const char *format, const char *file_name, int mode, ...)
{
    va_list arg_list;
    why_string_buffer *buffer;
    int file_descriptor;
    int length;

    va_start(arg_list, mode);
    file_descriptor = open(file_name, mode);
    if (file_descriptor < 0)
        return 0;
    buffer = why_string_buffer_create_formatted(format, &arg_list);
    length = write(file_descriptor, buffer->content, buffer->current - buffer->content);

    va_end(arg_list);
    why_string_buffer_destory(&buffer);
    close(file_descriptor);

    return length;
}