#include "why_lib.h"

why_stack *why_stack_create(int item_capacity, void *(*copy)(), void (*destroy)())
{
    return why_vector_create(item_capacity, copy, destroy);
}

int why_stack_reallocate(why_stack *vector, int extra_item_capacity)
{
    return why_vector_reallocate(vector, extra_item_capacity);
}

void *why_stack_pop(why_stack *vector)
{
    return why_vector_pop(vector);
}

int why_stack_push(why_stack *vector, const void *item)
{
    return why_vector_push(vector, item);
}

int why_stack_get_length(const why_stack *vector)
{
    return why_vector_get_length(vector);
}
int why_stack_is_sorted(const why_stack *vector, int (*comapre)())
{
    return why_stack_is_sorted(vector, comapre);
}