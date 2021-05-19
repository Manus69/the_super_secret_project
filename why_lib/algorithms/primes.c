#include "why_display_functions.h"
#include "why_math_functions.h"
#include "why_primes.h"
#include "why_memory_functions.h"
#include "why_macros.h"
#include "why_constants.h"

#include "why_printf_functions.h" //
#include "why_vector_functions.h"

static why_vector *init_primes()
{
    why_vector *primes;
    int p;

    primes = why_vector_create(DEFAULT, why_memory_copy_int, why_memory_destroy);
    p = 2;
    why_vector_push(primes, &p);

    return primes;
}

int why_prime_is_prime(const why_vector *primes, unsigned int number)
{
    unsigned int p;
    int n;
    int length;

    n = 0;
    length = why_vector_get_length(primes);

    if (!length)
        return true;
    
    while (n < length)
    {
        p = *(int *)why_vector_at(primes, n);
        if (number % p == 0)
            return false;
        if (p * p > number)
            break;
        
        n ++;
    }

    return true;
}

int why_prime_is_prime_naive(unsigned int number)
{
    unsigned int n;

    n = 2;

    while ((n * n) <= number)
    {
        if (number % n == 0)
            return false;
        n ++;
    }

    return true;
}

why_vector *why_primes_get_primes(unsigned int limit)
{
    why_vector *primes;
    unsigned int n;

    primes = init_primes();
    n = *(unsigned int *)why_vector_last(primes) + 1;

    while (n <= limit)
    {
        if (why_prime_is_prime(primes, n))
        {
            why_vector_push(primes, &n);
        }
        n ++;
    }

    return primes;
}

why_vector *why_primes_get_n_primes_naive(unsigned int n)
{
    why_vector *primes;
    unsigned int number;

    if (n <= 0)
        return NULL;
    primes = init_primes();
    number = 3;
    while ((unsigned int )why_vector_get_length(primes) < n)
    {
        if (why_prime_is_prime_naive(number))
            why_vector_push(primes, &number);
        number ++;
    }

    return primes;
}

why_vector *why_primes_get_n_primes(int N)
{
    why_vector *primes;
    unsigned int n;

    primes = init_primes();
    n = *(unsigned int *)why_vector_last(primes) + 1;
    N = N - why_vector_get_length(primes);

    if (N < 0)
        return primes;

    while (N)
    {
        if (why_prime_is_prime(primes, n))
        {
            why_vector_push(primes, &n);
            N --;
        }
        n ++;
    }

    return primes;
}

unsigned int why_primes_get_next_prime(unsigned int n)
{
    while (!why_prime_is_prime_naive(n))
        n ++;
    
    return n;
}