#ifndef WHY_VECTOR_STRUCTURE_H
#define WHY_VECTOR_STRUCTURE_H

struct why_vector
{    
    void (*destructor)();
    void *(*copy_function)();

    void **content;
    // void *last_element;

    int current_index;
    int item_capacity; 
};

#endif