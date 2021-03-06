#include "why_memory_functions.h"

#include <limits.h>

static inline unsigned int rotate_bits_right(unsigned int number, unsigned int shift)
{
    return (number >> shift) | (number << (sizeof(number) * CHAR_BIT - shift));
}

static inline unsigned int rotate_bits_left(unsigned int number, unsigned int shift)
{
    return (number << shift) | (number >> (sizeof(number) * CHAR_BIT - shift));
}

unsigned int why_memory_rotate_bits(void *stuff, int n)
{
    unsigned int number;
    unsigned int shift;

    number = *(unsigned int *)stuff;
    if (n < 0)
    {
        shift = -n % sizeof(unsigned int);
        number = rotate_bits_left(number, shift);
    }
    else if (n > 0)
    {
        shift = n % sizeof(unsigned int);
        number = rotate_bits_right(number, shift);
    }
    
    return number;
}

//this is bricked; implement bitfields first;
unsigned int why_memory_rotate_byte_bits(void *stuff, int n)
{
    unsigned char *current_byte;
    unsigned int number;
    int byte_number;

    number = 0;
    byte_number = 0;
    current_byte = (unsigned char *)stuff;
    while (byte_number < (int)sizeof(unsigned int))
    {
        *current_byte = why_memory_get_byte(stuff, byte_number);
        *current_byte = why_memory_rotate_bits(current_byte, n);
        number |= (*current_byte << (CHAR_BIT * byte_number));
        byte_number ++;
    }

    return number;
}

unsigned int why_memory_flip_bits(unsigned int n)
{
    return ~0 ^ n;
}

unsigned int why_memory_get_complement(unsigned int n)
{
    return (~0 ^ n) + 1;
}