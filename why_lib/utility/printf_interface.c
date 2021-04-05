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

static int string_buffer_flush(why_string_buffer *string_buffer, int number_of_bytes)
{
    int length;

    length = write(STDOUT_FILENO, string_buffer->content, number_of_bytes);
    why_string_buffer_reset(string_buffer);

    return length;
}

int why_printf(const char *format, ...)
{
    va_list arg_list;
    int length;
    static int content_length;
    static why_string_buffer *string_buffer;


    va_start(arg_list, format);
    length = 0;
    if (!format && !string_buffer)
        return 0;
    if (!format)
    {
        length = string_buffer_flush(string_buffer, content_length);
        content_length = 0;
        why_string_buffer_destory(&string_buffer);
        va_end(arg_list);

        return length;
    }
    string_buffer = why_string_buffer_create_formatted(format, &arg_list);
    content_length = string_buffer->current - string_buffer->content;

    if (content_length > PRINTF_FLUSH_THRESHOLD)
    {
        length = string_buffer_flush(string_buffer, content_length);
        content_length = 0;
    }

    va_end(arg_list);
    // why_string_buffer_destory(&string_buffer);

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