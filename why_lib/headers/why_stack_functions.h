#ifndef WHY_STACK_FUNCTIONS_H
#define WHY_STACK_FUNCTIONS_H

#include "why_typedefs.h"

why_stack *why_stack_create(int item_capacity, void *(*copy)(), void (*destroy)());

int why_stack_reallocate(why_stack *vector, int extra_item_capacity);

void *why_stack_pop(why_stack *vector);

int why_stack_push(why_stack *vector, const void *item);
int why_stack_get_length(const why_stack *vector);
int why_stack_is_sorted(const why_stack *vector, int (*comapre)());

#endif