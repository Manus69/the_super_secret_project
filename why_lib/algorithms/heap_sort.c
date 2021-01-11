#include "why_lib.h"

#include "why_vector.h"
#include "why_constants.h"


void why_downheap(void **array, int size, int index, int (*compare)())
{
    int left_child_index;
    int right_child_index;
    int next_index;

    left_child_index = 2 * index + 1;
    right_child_index = 2 * index + 2;

    if ((left_child_index < size) && (right_child_index < size))
    {
        next_index = right_child_index;

        if (compare(array[left_child_index], array[right_child_index]) > 0)
            next_index = left_child_index;

        if (compare(array[index], array[next_index]) < 0)
        {
            SWAP(array, void *, index, next_index);
            why_downheap(array, size, next_index, compare);
        }
    }
    else if (left_child_index < size)
    {
        if (compare(array[index], array[left_child_index]) < 0)
        {
            SWAP(array, void *, index, left_child_index);
        }
    }
}

void why_heapify(void **array, int size, int (*compare)())
{
    int index;

    if (size <= 1)
        return ;

    index = size - 1;
    if (index % 2)
        index = (index - 1) / 2;
    else
        index = (index - 2) / 2;
    
    while (index >= 0)
    {
        why_downheap(array, size, index, compare);
        index --;
    }
}

void *why_heap_delete_root(void **heap, int size, int (*compare)())
{
    void *root;

    root = heap[0];

    if (size > 1)
    {
        SWAP(heap, void *, 0, size - 1);
        why_downheap(heap, size - 1, 0, compare);
    }

    return root;
}

void why_sort_array_heapsort(void **array, int size, int (*compare)())
{
    why_heapify(array, size, compare);
    while (size)
    {
        why_heap_delete_root(array, size, compare);
        size --;
    }
}

void why_sort_vector_heapsort(why_vector *vector, int (*compare)())
{
    why_sort_array_heapsort(vector->content, why_vector_get_length(vector), compare);
}

// #define LIMIT 1 << 10
// void why_sort_heapsort_hybrid(void **array, int size, int (*compare)())
// {
//     if (size < LIMIT)
//     {
//         why_sort_array_insert(array, size, compare);

//         return ;
//     }
//     why_heapify(array, size, compare);
//     while (size >= LIMIT)
//     {
//         why_heap_delete_root(array, size, compare);
//         size --;
//     }
//     why_sort_array_insert(array, size, compare);
// }

// static inline void *get_left_child(void **heap, int size, int index)
// {
//     int child_index;

//     child_index = 2 * index + 1;
//     return child_index < size ? heap[2 * index + 1] : NULL;
// }

// static inline void *get_right_child(void **heap, int size, int index)
// {
//     int child_index;

//     child_index = 2 * index + 2;
//     return child_index < size ? heap[2 * index + 2] : NULL;
// }

// static inline void *get_parent(void **heap, int index)
// {
//     if (index == 0)
//         return NULL;

//     return heap[(index - 1) / 2];
// }

// int why_heap_is_heap(void **heap, int size, int (*compare)())
// {
//     int n;
//     int limit;
//     void *left_child;
//     void *right_child;

//     n = 0;
//     limit = (size - 1) / 2;
//     while (n <= limit)
//     {
//         left_child = get_left_child(heap, size, n);
//         right_child = get_right_child(heap, size, n);

//         if (compare(heap[n], left_child) < 0)
//             return false;
//         if (compare(heap[n], right_child) < 0)
//             return false;
        
//         n ++;
//     }

//     return true;
// }