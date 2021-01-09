#include "why_memory.h"

//does it work?
#define CAST_COPY(target, source, type) *(type *)target = *(type *)source

void *why_memory_copy(void *destination, const void *source, int number_of_bytes)
{
    unsigned char *lhs;
    unsigned char *rhs;

    if (number_of_bytes <= 0 || !source)
        return destination;

    lhs = (unsigned char *)destination;
    rhs = (unsigned char *)source;

    while (number_of_bytes)
    {
        *lhs = *rhs;
        lhs ++;
        rhs ++;
        number_of_bytes --;
    }

    return destination;
}

void *why_memory_shallow_copy(const void *source)
{
    return (void *)source;
}

void *why_memory_set(void *location, unsigned char value, int number_of_bytes)
{
    unsigned char *lhs;

    if (number_of_bytes <= 0)
        return location;

    lhs = (unsigned char *)location;

    while (number_of_bytes)
    {
        *lhs = value;
        lhs ++;
        number_of_bytes --;
    }

    return location;
}

void *why_memory_get_zeroes(int number_of_bytes)
{
    void *block;

    if ((block = malloc(number_of_bytes)))
    {
        why_memory_set(block, 0, number_of_bytes);

        return block;
    }
    
    return NULL;
}

void why_memory_destroy(void **thing)
{
    if (!thing || !*thing)
        return ;

    free(*thing);
    *thing = NULL;
}

void why_memory_pointer_swap(void **lhs, void **rhs)
{
    void *pointer;

    if (!lhs || !rhs)
        return ;
        
    pointer = *lhs;
    *lhs = *rhs;
    *rhs = pointer;
}

unsigned char why_memory_get_byte(void *stuff, int n)
{
    unsigned char *byte_pointer;

    byte_pointer = (unsigned char *)stuff;

    return *(byte_pointer + n);
}