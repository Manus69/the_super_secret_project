// #include "why_math.h"
#include "why_memory.h"

#include "why_display.h" //

static inline int swap(void **array, int left_index, int right_index)
{
    void *store;

    store = array[left_index];
    array[left_index] = array[right_index];
    array[right_index] = store;

    return SUCCESS;
}


static void copy_pointers(void **destination, void **source, int number_of_items)
{
    int n;

    n = 0;
    while (n < number_of_items)
    {
        destination[n] = source[n];
        n ++;
    }
}

static inline void **get_sub_array(void **array, int left_index, int number_of_items)
{
    void **subarray;

    subarray = malloc(sizeof(void *) * (number_of_items));

    if (!subarray)
        return NULL;
    
    // why_memory_copy((void *)subarray, array[left_index], number_of_items * sizeof(void *));
    copy_pointers(subarray, &array[left_index], number_of_items);
    //
    // why_display_array(subarray, number_of_items, why_display_int);
    //
    
    return subarray;     
}

static void **join_sorted(void **left_array, void **right_array, int n_items_left, int n_items_right, int (*compare)())
{
    void **result;
    int n;
    int number_of_items;

    number_of_items = n_items_left + n_items_right;
    result = malloc(sizeof(void *) * (number_of_items));

    if (!result)
        return NULL;

    n = 0;
    while (n < number_of_items)
    {
        if (!n_items_left)
        {
            result[n] = *right_array;
            right_array ++;
            n_items_right --;
        }
        else if (!n_items_right)
        {
            result[n] = *left_array;
            left_array ++;
            n_items_left --;
        }
        else if (compare(*left_array, *right_array) > 0)
        {
            result[n] = *right_array;
            right_array ++;
            n_items_right --;
        }
        else
        {
            result[n] = *left_array;
            left_array ++;
            n_items_left --;
        }

        n ++;
    }

    return result;
}

void **why_sort_array_merge(void **array, int number_of_items, int (*compare)())
{
    void **lhs;
    void **rhs;
    int half_number;

    if (number_of_items == 1)
        return array;
    else if (number_of_items == 2)
    {
        if (compare(array[0], array[1]) > 0)
            // swap(array, 0, 1);
            SWAP(array, void *, 0, 1);

        return array;
    }

    half_number = number_of_items / 2;
    lhs = get_sub_array(array, 0, half_number);
    rhs = get_sub_array(array, half_number, number_of_items - half_number);
    free(array);

    return join_sorted(why_sort_array_merge(lhs, half_number, compare),
    why_sort_array_merge(rhs, number_of_items - half_number, compare), half_number, number_of_items - half_number, compare);
}