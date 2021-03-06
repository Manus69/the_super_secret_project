#include "why_typedefs.h"
#include "why_vector_structure.h"
#include "why_memory_functions.h"

void *why_vector_accumualte(const why_vector *vector, int start, int number_of_items, void *(*combine)())
{
    void *accumulator;

    if (!vector || !combine)
        return NULL;

    if (!number_of_items)
        return NULL;

    accumulator = NULL;

    while (number_of_items)
    {
        accumulator = combine(accumulator, vector->content[start]);
        start ++;
        number_of_items --;
    }

    return accumulator;
}