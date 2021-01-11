#include "why_memory.h"
#include "why_math.h"
#include "why_vector.h"

#include "why_display.h" //

static inline int get_item_count(int size, int frame_size)
{
    if (!size)
        return 0;
    
    return frame_size <= size ? frame_size : MIN(size, frame_size);
}

//this is tricky
void **make_a_pass(void **target, void **source, int size, int frame_size, int (*compare)())
{
    int n;
    int left_frame_index;
    int right_frame_index;
    int left_items_count;
    int right_items_count;

    n = 0;
    left_frame_index = 0;
    left_items_count = get_item_count(size, frame_size);
    size -= left_items_count;
    right_items_count = get_item_count(size, frame_size);
    size -= right_items_count;
    right_frame_index = left_frame_index + left_items_count;

    while (left_items_count || right_items_count)
    {
        if (!right_items_count)
        {
            target[n] = source[left_frame_index];
            left_frame_index ++;
            left_items_count --;
        }
        else if (!left_items_count)
        {
            target[n] = source[right_frame_index];
            right_frame_index ++;
            right_items_count --;
        }
        else if (compare(source[left_frame_index], source[right_frame_index]) < 0)
        {
            target[n] = source[left_frame_index];
            left_frame_index ++;
            left_items_count --;
        }
        else
        {
            target[n] = source[right_frame_index];
            right_frame_index ++;
            right_items_count --;
        }
        n ++;

        if (!left_items_count && !right_items_count)
        {
            left_items_count = get_item_count(size, frame_size);
            size -= left_items_count;
            left_frame_index = right_frame_index;
            right_items_count = get_item_count(size, frame_size);
            size -= right_items_count;
            right_frame_index = left_frame_index + left_items_count;
        }
    }

    return target;
}

// [ ... x x x x ... ]
// [   |____||____|  ]

void **why_sort_array_merge_mk2(void **array, int size, int (*compare)())
{
    void **second_array;
    int frame_size;

    if (size <= 1)
        return array;

    if ((second_array = malloc(sizeof(void *) * size)))
    {
        frame_size = 1;
        return make_a_pass(second_array, array, size, frame_size, compare);
    }

    return NULL;
}

void why_sort_vector_merge_mk2(why_vector *vector, int (*compare)())
{
    void **second_array;
    void **first_array;
    void **store;
    int frame_size;
    int size;

    size = why_vector_get_length(vector);

    if (size <= 1)
        return ;

    if ((second_array = malloc(sizeof(void *) * size + 1)))
    {
        frame_size = 1;
        first_array = vector->content;
        while (frame_size < size)
        {
            make_a_pass(second_array, first_array, size, frame_size, compare);
            
            //
            // why_display_array(second_array, size, why_display_string);
            //

            vector->content = second_array;
            store = second_array;
            second_array = first_array;
            first_array = store;

            frame_size *= 2;

        }
        if (vector->content == first_array)
            free(second_array);
        else
            free(first_array);
    }
}