#include "why_constants.h"
#include "why_typedefs.h"
#include "why_vector_structure.h"
#include "why_vector_functions.h"

void why_sort_array_insert(void **array, int left_index, int right_index, int (*compare)())
{
    int n;
    int current_index;
    void *store;

    if (right_index - left_index < 1)
        return ;

    current_index = 1;

    while (current_index <= right_index)
    {
        n = current_index;
        store = array[n];

        while (n > left_index && (compare(store, array[n - 1]) < 0))
        {
            array[n] = array[n - 1];
            n --;
        }
        current_index ++;
        array[n] = store;
    }
}

void why_sort_vector_insert(why_vector *vector, int (*compare)())
{
    why_sort_array_insert(vector->content, 0, why_vector_get_length(vector) - 1, compare);
}