#ifndef WHY_STRING_BUFFER_FUNCTIONS_H
#define WHY_STRING_BUFFER_FUNCTIONS_H

#include "why_typedefs.h"

why_string_buffer *why_string_buffer_create(int size);

char *why_string_buffer_get_content(const why_string_buffer *buffer);

void why_string_buffer_reset(why_string_buffer *buffer);
void *why_string_buffer_append_string_rvp(why_string_buffer *buffer, const char *string);

int why_string_buffer_append_string(why_string_buffer *buffer, const char *string);
int why_string_buffer_append_from_string(why_string_buffer *buffer, const char *string, int n_chars);
int why_string_buffer_append_char(why_string_buffer *buffer, char c, int number_of_times);
int why_string_buffer_check_capacity(why_string_buffer *buffer, int requirement);

void why_string_buffer_destory(why_string_buffer **buffer);
void why_string_buffer_reset(why_string_buffer *buffer);

#endif