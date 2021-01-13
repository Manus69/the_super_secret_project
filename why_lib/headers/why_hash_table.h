#ifndef WHY_HASH_TABLE_H
#define WHY_HASH_TABLE_H

struct why_hash_table
{
    unsigned int (*hash_function)();

    void **table;
    unsigned int size;
    
};

#endif