#include "why_display_functions.h"
#include "why_math_functions.h"
#include "why_primes.h"
#include "why_memory_functions.h"
#include "why_macros.h"
#include "why_constants.h"

#include "why_printf_functions.h" //
#include "why_vector_functions.h"

#define END -1

static int *get_numbers(int limit)
{
    int n;
    int *numbers;

    if (limit < 2)
        limit = 2;
    if (limit == INT_MAX)
        limit = INT_MAX - 2;

    numbers = malloc(sizeof(int) * (limit + 2));
    if (!numbers)
        return NULL;

    numbers[0] = 0;
    numbers[1] = 0;

    n = 2;
    while (n <= limit)
    {
        numbers[n] = n;
        n ++;
    }
    
    numbers[n] = END;

    return numbers;
}

static void divide_through(int p, int *numbers)
{   
    while (*numbers != END)
    {
        if (*numbers % p == 0)
            *numbers = 0;
        numbers ++;
    }
}

static int get_next_prime(int *numbers)
{
    while (*numbers != END)
    {
        if (*numbers != 0)
            return *numbers;
        
        numbers ++;
    }

    return END;
}

static void sieve(why_vector *primes, int *numbers, int limit)
{
    int max_prime;

    max_prime = *(int *)why_vector_at(primes, why_vector_get_length(primes) - 1);
    while (true)
    {
        if (max_prime * max_prime <= limit)
        {
            divide_through(max_prime, numbers);
        }

        max_prime = get_next_prime(numbers + max_prime + 1);
        if (max_prime >= limit || max_prime == END)
        {
            break ;
        }
        why_vector_push(primes, &max_prime);
    }
}

static void sieve_while(why_vector *primes, int *numbers, int n)
{
    int max_prime;
    int limit;

    limit = numbers[n];
    max_prime = *(int *)why_vector_at(primes, why_vector_get_length(primes) - 1);
    while (why_vector_get_length(primes) < n)
    {
        if (max_prime * max_prime <= limit)
        {
            divide_through(max_prime, numbers);
        }

        max_prime = get_next_prime(numbers + max_prime + 1);
        if (max_prime == END)
        {
            break ;
        }
        why_vector_push(primes, &max_prime);
    }
}

static why_vector *init_primes()
{
    why_vector *primes;
    int p;

    primes = why_vector_create(DEFAULT, why_memory_copy_int, why_memory_destroy);
    p = 2;
    why_vector_push(primes, &p);

    return primes;
}

why_vector *why_primes_get_primes(int limit)
{
    why_vector *primes;
    int *numbers;

    numbers = get_numbers(limit);
    primes = init_primes();

    sieve(primes, numbers, limit);

    free(numbers);
    return primes;
}

why_vector *why_primes_get_n_primes(int n)
{
    why_vector *primes;
    int *numbers;

    numbers = get_numbers(INT_MAX); //this is wrong
    primes = init_primes();

    sieve_while(primes, numbers, n);

    free(numbers);
    return primes;
}