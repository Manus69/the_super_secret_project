#include "why_lib.h"

#include "why_math.h"
#include "why_vector.h"

void *why_vector_accumualte(const why_vector *vector, int start, int number_of_items, char *(*combine)())
{
    // int length;
    // int n;
    void *accumulator;

    if (!vector || !combine)
        return NULL;

    if (!number_of_items)
        return NULL;

    // accumulator = combine(NULL, vector->content[start]);
    // start ++;

    accumulator = NULL;

    while (number_of_items)
    {
        accumulator = combine(accumulator, vector->content[start]);
        start ++;
        number_of_items --;
    }

    return accumulator;
}