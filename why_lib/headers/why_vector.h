#ifndef WHY_VECTOR_H
#define WHY_VECTOR_H

#define DEFAULT_CAPACITY 32

void why_vector_content_destroy(void **content, int number_of_items, void (*destroy)());

struct why_vector
{    
    void (*destructor)();
    void *(*copy_function)();

    void **content;
    void *last_element;

    int current_index;
    int item_capacity; 
};

#endif
