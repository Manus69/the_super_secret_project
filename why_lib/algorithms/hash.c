#include "why_lib.h"

#include "why_hash_table.h"
#include "why_math.h"

#define ALPHABET_SIZE 71 //a prime close to the actual number of symbols; does it matter?
#define LARGE_PRIME 433494437

unsigned int why_hash_string(const char *string, unsigned int table_size)
{
    unsigned int hash_value;
    int n;

    hash_value = 0;
    n = 0;
    while (string[n])
    {
        hash_value = (hash_value * ALPHABET_SIZE + string[n]) % table_size;
        n ++;
    }

    return hash_value;
}

why_hash_table *why_hash_table_create(unsigned int size, unsigned int (*hash_function)())
{
    struct why_hash_table *hash_table;
    unsigned int n;

    size = why_math_get_next_prime(size);

    if (!size || !hash_function)
        return NULL;
    
    if ((hash_table = malloc(sizeof(struct why_hash_table))))
    {
        if ((hash_table->table = malloc(sizeof(void *) * size)))
        {
            hash_table->size = size;
            hash_table->hash_function = hash_function;

            n = 0;
            while (n < size)
            {
                hash_table->table[n] = NULL;
                n ++;
            }

            return hash_table;
        }
    }

    return NULL;
}

int why_hash_table_add(why_hash_table *table, void *item)
{
    ;
}

void why_hash_table_destroy(why_hash_table **table)
{
    ;
}