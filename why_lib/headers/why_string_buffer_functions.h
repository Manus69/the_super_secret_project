#ifndef WHY_STRING_BUFFER_FUNCTIONS_H
#define WHY_STRING_BUFFER_FUNCTIONS_H

#include "why_typedefs.h"

why_string_buffer *why_string_buffer_create(int size);

char *why_string_buffer_get_content(const why_string_buffer *buffer);

void *why_string_buffer_write_string_rvp(why_string_buffer *buffer, const char *string);

int why_string_buffer_write_string(why_string_buffer *buffer, const char *string);
// int why_string_buffer_write_int(why_string_buffer *buffer, int number);
int why_string_buffer_check_capacity(why_string_buffer *buffer, int requirement);

void why_string_buffer_destory(why_string_buffer **buffer);

#endif