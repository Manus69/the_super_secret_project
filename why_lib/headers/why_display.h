#ifndef WHY_DISPLAY_H
#define WHY_DISPLAY_H

#include "why_lib.h"

void why_display_string(const char *literal);
void why_display_int(int *n);
void why_display_double(double *x);
void why_display_list(const struct why_list *list, void (*display_function)());
void why_display_vector(const struct why_vector *vector, void (*display_function)());
void why_display_array(void **array, int number_of_elements, void (*display_functon)());
void why_display_hash_table(const why_hash_table *table, void (*display)()); //rework this

#endif