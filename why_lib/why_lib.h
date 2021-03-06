#ifndef WHY_LIB_H
#define WHY_LIB_H


#include "headers/why_typedefs.h"
#include "headers/why_string_functions.h"
#include "headers/why_display.h"

//buffer


//file
void *why_file_read_all_lines_into_structure
(why_buffer *buffer, char terminator, void *structure, int (*push)());

char *why_file_read_file_into_string(const char *file_name);

why_vector *why_file_read_all_lines(const char *file_name);




#endif