#ifndef WHY_VECTOR_FUNCTIONS_H
#define WHY_VECTOR_FUNCTIONS_H

#include "why_typedefs.h"

why_vector *why_vector_create(int item_capacity, void *(*copy)(), void (*destroy)());

int why_vector_reallocate(why_vector *vector, int extra_item_capacity);

void *why_vector_at(const why_vector *vector, int index);
void *why_vector_pop(why_vector *vector);
void *why_vector_apply_function_mk2(why_vector *vector, int (*function)(), int failure_value);
void *why_vector_first(const why_vector *vector);
void *why_vector_last(const why_vector *vector);

int why_vector_replace_at(why_vector *vector, const void *item, int index);
int why_vector_push(why_vector *vector, const void *item);
int why_vector_get_length(const why_vector *vector);
int why_vector_get_capacity(const why_vector *vector);
int why_vector_is_sorted(const why_vector *vector, int (*comapre)());
int why_vector_swap(why_vector *vector, int j, int k);
int why_vector_nullify(why_vector *vector);
int why_vector_apply_function(why_vector *vector, void (*function)());
int why_vector_append_and_destroy(why_vector *left, why_vector *right);

void why_vector_destroy(why_vector **vector);
// void why_vector_content_destroy(void **content, int number_of_items, void (*destroy)());

void *why_vector_accumualte(const why_vector *vector, int start, int number_of_items, void *(*combine)());

#endif