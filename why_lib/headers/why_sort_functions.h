#ifndef WHY_SORT_FUNCTIONS_H
#define WHY_SORT_FUNCTIONS_H

#include "why_typedefs.h"

void why_sort_array_heapsort(void **array, int size, int (*compare)());
void why_sort_vector_heapsort(why_vector *vector, int (*compare)());

void **why_sort_array_merge_mk2(void **array, int size, int (*compare)());
void **why_sort_array_merge(void **array, int number_of_items, int (*compare)());
void why_sort_vector_merge_mk2(why_vector *vector, int (*compare)());

void why_sort_array_insert(void **array, int left_index, int right_index, int (*compare)());
void why_sort_vector_insert(why_vector *vector, int (*compare)());

#endif