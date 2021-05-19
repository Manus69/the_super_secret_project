#ifndef WHY_PRIMES_H
#define WHY_PRIMES_H

#include "why_vector_functions.h"


typedef unsigned long integer; //i should do it properly

int why_prime_is_prime_naive(unsigned int number);
unsigned int why_primes_get_next_prime(unsigned int n);

why_vector *why_primes_get_primes(unsigned int limit);
why_vector *why_primes_get_n_primes(int n);
why_vector *why_primes_get_n_primes_naive(unsigned int n);

#endif