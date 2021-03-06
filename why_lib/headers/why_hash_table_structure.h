#ifndef WHY_HASH_TABLE_STRUCTURE_H
#define WHY_HASH_TABLE_STRUCTURE_H

struct why_hash_table
{
    unsigned int (*hash_function)();
    void (*destructor)();
    void *(*copy_function)();

    void **table;
    unsigned int size;
    
};

#endif