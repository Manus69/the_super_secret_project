#ifndef WHY_MEMORY_FUNCTIONS_H
#define WHY_MEMORY_FUNCTIONS_H

#include <stdlib.h>

void *why_memory_copy(void *destination, const void *source, int number_of_bytes);
void *why_memory_copy_double(double x);
void *why_memory_copy_backwards(void *destination, const void *source, int number_of_bytes);
void *why_memory_shallow_copy(const void *source);
void *why_memory_set(void *location, unsigned char value, int number_of_bytes);
void *why_memory_get_zeroes(int number_of_bytes);

void *set_int_value(void *target, const void *item, int dummy);
void *set_double_value(void *target, const void *item, int dummy);

void why_memory_destroy(void **thing);
void why_memory_pointer_swap(void **lhs, void **rhs);

unsigned int why_memory_rotate_bits(void *stuff, int n);
unsigned int why_memory_rotate_byte_bits(void *stuff, int n);
unsigned int why_memory_flip_bits(unsigned int n);
unsigned int why_memory_get_complement(unsigned int n);

unsigned char why_memory_get_byte(void *stuff, int n);

#endif