#ifndef WHY_MEMORY_H
#define WHY_MEMORY_H

#include <stdlib.h>

#define DEFAULT_ITEM_SIZE (int)sizeof(void *)
#define SWAP(array, type, li, ri) {type _store = array[li]; array[li] = array[ri]; array[ri] = _store;}

void *why_memory_copy(void *destination, const void *source, int number_of_bytes);
void *why_memory_shallow_copy(const void *source);
void *why_memory_set(void *location, unsigned char value, int number_of_bytes);
void *why_memory_get_zeroes(int number_of_bytes);

void *set_int_value(void *target, const void *item, int dummy);
void *set_double_value(void *target, const void *item, int dummy);

void why_memory_destroy(void **thing);
void why_memory_pointer_swap(void **lhs, void **rhs);

unsigned int why_memory_rotate_bits(void *stuff, int n);
unsigned int why_memory_rotate_byte_bits(void *stuff, int n);

unsigned char why_memory_get_byte(void *stuff, int n);

#endif