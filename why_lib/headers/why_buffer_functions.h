#ifndef WHY_BUFFER_FUNCTIONS_H
#define WHY_BUFFER_FUNCTIONS_h

#include "why_typedefs.h"


void why_buffer_reset(why_buffer *buffer);

char *why_buffer_flush(why_buffer *buffer);

enum why_buffer_status why_buffer_read_into(why_buffer *buffer, int number_of_bytes);
enum why_buffer_status why_buffer_read_into_default(why_buffer *buffer);
enum why_buffer_status why_buffer_shift_read_position(why_buffer *buffer, int shift);
enum why_buffer_status why_buffer_get_status(const why_buffer *buffer);

//
why_buffer *why_buffer_create(const char *file_name, int capacity, int read_size);

void why_buffer_destroy(why_buffer **buffer);

char *why_buffer_read_from(why_buffer *buffer, int number_of_bytes);

#endif