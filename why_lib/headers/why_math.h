#ifndef WHY_MATH_H
#define WHY_MATH_H

#include "why_constants.h"
#include "why_memory.h"

#define MAX(a, b) ((a) > (b)) ? (a) : (b)
#define MIN(a, b) ((a) < (b)) ? (a) : (b)

unsigned int why_math_random(unsigned int seed, unsigned int max);

#endif