#ifndef WHY_HEAP_H
#define WHY_HEAP_H

#include <stdlib.h>

#include "why_constants.h"
#include "why_memory.h"

int why_heap_is_heap(void **heap, int size, int (*compare)());
void why_downheap(void **array, int size, int index, int (*compare)());
void why_heapify(void **array, int size, int (*compare)());
void why_sort_heapsort(void **array, int size, int (*compare)());
void why_sort_heapsort_hybrid(void **array, int size, int (*compare)());

#endif