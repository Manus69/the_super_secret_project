#include "why_math.h"

//naive
int why_math_is_prime(unsigned int number)
{
    unsigned int n;

    n = 2;
    while ((n * n) <= number)
    {
        if (number % n)
            return false;
        n ++;
    }

    return true;
}

unsigned int why_math_get_next_prime(unsigned int number)
{
    int is_prime;

    while ((is_prime = why_math_is_prime(number)) == false)
    {
        number ++;
    }

    return number;
}