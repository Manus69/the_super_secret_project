#include "why_hash_table_structure.h"
#include "why_primes.h"
#include "why_typedefs.h"
#include "why_constants.h"
#include "why_memory_functions.h"
#include "why_math_functions.h"
#include "why_list_functions.h"

unsigned int why_hash_string(const char *string, unsigned int table_size)
{
    unsigned int hash_value;
    int n;

    table_size = !table_size ? HASH_LARGE_PRIME : table_size;
    hash_value = 0;
    n = 0;
    while (string[n])
    {
        hash_value = (hash_value * HASH_ALPHABET_SIZE + string[n]) % table_size;
        n ++;
    }

    return hash_value;
}

why_hash_table *why_hash_table_create(unsigned int size, unsigned int (*hash_function)(), void *(*copy)(), void (*destroy)())
{
    struct why_hash_table *hash_table;
    unsigned int n;

    size = why_primes_get_next_prime(size);

    if (!size || !hash_function)
        return NULL;
    
    if ((hash_table = malloc(sizeof(struct why_hash_table))))
    {
        if ((hash_table->table = malloc(sizeof(void *) * size)))
        {
            hash_table->size = size;
            hash_table->hash_function = hash_function;
            hash_table->copy_function = copy ? copy : why_memory_shallow_copy;
            hash_table->destructor = destroy ? destroy : why_memory_destroy;

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

void **why_hash_table_get_table(const why_hash_table *table)
{
    return table->table;
}

unsigned int why_hash_table_get_size(const why_hash_table *table)
{
    return table->size;
}

int why_hash_table_add(why_hash_table *table, void *item)
{
    unsigned int hash_value;

    hash_value = table->hash_function(item, table->size);

    if (!table->table[hash_value])
    {
        table->table[hash_value] = why_list_create(table->copy_function, table->destructor);
    }
    why_list_push((why_list *)(table->table[hash_value]), item);

    return SUCCESS;    
}

void *why_hash_table_search(why_hash_table *table, void *item, int (*compare)())
{
    unsigned int hash_value;
    why_list *list;

    hash_value = table->hash_function(item, table->size);
    list = table->table[hash_value];

    if (!list)
        return NULL;

    return why_list_search(list, item, compare);
}

//this is bad
void why_hash_table_apply(why_hash_table *table, void (*top_function)(), void (*bottom_function)())
{
    unsigned int n;

    n = 0;
    while (n < table->size)
    {
        top_function(table->table[n], bottom_function);
        n ++;
    }
}

void why_hash_table_destroy(why_hash_table **table)
{
    unsigned int n;

    n = 0;
    while (n < (*table)->size)
    {
        if ((*table)->table[n])
            why_list_destroy((why_list **)&(*table)->table[n]);
        n ++;
    }
    free((*table)->table);
    why_memory_destroy((void **)table);
}