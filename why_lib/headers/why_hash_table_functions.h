#ifndef WHY_HASH_TABLE_FUNCTIONS_H
#define WHY_HASH_TABLE_FUNCTIONS_H

#include "why_typedefs.h"

why_hash_table *why_hash_table_create(unsigned int size, unsigned int (*hash_function)(), void *(*copy)(), void (*destroy)());

unsigned int why_hash_string(const char *string, unsigned int table_size);
int why_hash_table_add(why_hash_table *table, void *item);

void *why_hash_table_search(why_hash_table *table, void *item, int (*compare)());

void why_hash_table_apply(why_hash_table *table, void (*top_function)(), void (*bottom_function)());
void why_hash_table_destroy(why_hash_table **table);

void **why_hash_table_get_table(const why_hash_table *table); // this is bad;
unsigned int why_hash_table_get_size(const why_hash_table *table); //

#endif