#include "why_memory_functions.h"

const unsigned int primes[] = {41, 661, 1299827, 21935983};
const unsigned int parameters[] = {12345, 1103515245};
// static unsigned int mask = 0xfffffff;

//this is suspicious
unsigned int why_math_random(unsigned int seed, unsigned int max)
{
    unsigned int result;
    static unsigned int previous_seed;
    static unsigned int current_seed;

    if (max == 0)
        return 0;

    if (!current_seed || (previous_seed != seed))
        current_seed = (parameters[1] * seed + parameters[0]);

    previous_seed = seed;

    current_seed = (current_seed * parameters[1] + parameters[0]);
    result = why_memory_rotate_bits(&current_seed, -2);
    // result = current_seed;

    return result % max;
}