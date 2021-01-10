#include "why_lib.h"
#include "why_vector.h"
#include "why_constants.h"
#include "why_memory.h"

static void **repopulate_content(void **new_array, void **old_array, int number_of_items)
{
    int n;

    n = 0;
    while (n < number_of_items)
    {
        new_array[n] = old_array[n];
        n ++;
    }

    return new_array;
}

static void destroy_vector_content(void **content, int number_of_items, void (*destroy)())
{
    int n;
    void *current_item;

    if (!content || !*content)
        return ;

    n = 0;
    while (n < number_of_items)
    {
        current_item = content[n];
        destroy(&current_item);
        n ++;
    }
}

why_vector *why_vector_create(int item_capacity, void *(*copy)(), void (*destroy)())
{
    why_vector *vector;
    
    item_capacity = item_capacity <= 0 ? DEFAULT_CAPACITY : item_capacity;
    copy = copy ? copy : why_memory_shallow_copy;
    destroy = destroy ? destroy : why_memory_destroy;

    if ((vector = malloc(sizeof(why_vector))))
    {
        if ((vector->content = malloc(sizeof(void *) * (item_capacity + 1)))) //do you need to memset?
        {
            vector->item_capacity = item_capacity;
            vector->current_index = 0;

            vector->copy_function = copy;
            vector->destructor = destroy;

            vector->last_element = vector->content[item_capacity];

            return vector;
        }
        free(vector);
    }

    return NULL;
}

int why_vector_reallocate(why_vector *vector, int extra_item_capacity)
{
    void **new_content;

    if (!vector || extra_item_capacity <= 0)
        return FAILURE;
    
    new_content = malloc((vector->item_capacity + extra_item_capacity + 1) * sizeof(void *));
    if (new_content)
    {
        new_content = repopulate_content(new_content, vector->content, vector->current_index);
        free(vector->content);

        vector->content = new_content;
        vector->item_capacity = vector->item_capacity + extra_item_capacity;
        vector->last_element = vector->content[vector->item_capacity];

        return SUCCESS;
    }

    return FAILURE;
}

void *why_vector_at(const why_vector *vector, int index)
{
    if (!vector || index < 0 || index >= vector->current_index)
        return NULL;
    
    return vector->content[index];
}

void *why_vector_pop(why_vector *vector)
{
    void *item;

    if (!vector || vector->current_index == 0)
        return NULL;
    
    item = vector->content[vector->current_index];
    vector->current_index --;

    return item;
}

void *why_vector_replace_at(why_vector *vector, const void *item, int index) //returns the old item
{
    void *old_item;

    if (!vector || index < 0)
        return NULL;
    
    old_item = vector->content[index];
    // vector->content[index] = (void *)item;
    vector->content[index] = vector->copy_function(item);

    return old_item;
}

int why_vector_push(why_vector *vector, const void *item)
{
    if (!vector)
        return FAILURE;
    
    if (vector->current_index == vector->item_capacity)
    {
        if (why_vector_reallocate(vector, vector->item_capacity) == FAILURE)
            return FAILURE;
    }

    vector->content[vector->current_index] = vector->copy_function(item);
    vector->current_index ++;

    return SUCCESS;
}

int why_vector_get_length(const why_vector *vector)
{
    return vector ? vector->current_index : 0;
}

int why_vector_is_sorted(const why_vector *vector, int (*comapre)())
{
    int index;

    if (!vector || !comapre || vector->current_index <= 1)
        return true;
    
    index = 1;
    while (index != vector->current_index)
    {
        if (comapre(vector->content[index - 1], vector->content[index]) > 0)
            return false;
        
        index ++;
    }

    return true;
}

int why_vector_swap(why_vector *vector, int j, int k)
{
    void *pointer;

    if (!vector || j < 0 || k < 0)
        return FAILURE;

    pointer = vector->content[j];
    vector->content[j] = vector->content[k];
    vector->content[k] = pointer;

    return SUCCESS;
}

void why_vector_destroy(why_vector **vector)
{
    if (!vector || !*vector)
        return ;
    
    destroy_vector_content((*vector)->content, (*vector)->current_index, (*vector)->destructor);
    why_memory_destroy((void **)&(*vector)->content);
    why_memory_destroy((void **)vector);
}