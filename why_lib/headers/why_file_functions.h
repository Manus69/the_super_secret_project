#ifndef WHY_FILE_FUNCTIONS_H
#define WHY_FILE_FUNCTIONS_H

#include "why_typedefs.h"

void *why_file_read_all_lines_into_structure
(why_buffer *buffer, char terminator, void *structure, int (*push)());

char *why_file_read_file_into_string(const char *file_name);

why_vector *why_file_read_all_lines(const char *file_name);

#endif