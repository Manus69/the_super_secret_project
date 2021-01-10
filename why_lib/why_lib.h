#ifndef WHY_LIB_H
#define WHY_LIB_H

typedef struct why_buffer why_buffer;
typedef struct why_vector why_vector;

#include "headers/why_string.h"
#include "headers/why_display.h"


//buffer
why_buffer *why_buffer_create(const char *file_name, int capacity, int read_size);

void why_buffer_destroy(why_buffer **buffer);

char *why_buffer_read_from(why_buffer *buffer, int number_of_bytes);

void *why_buffer_read_all_lines_into_structure
(why_buffer *buffer, char terminator, void *structure, int (*push)());

//vector
why_vector *why_vector_create(int item_capacity, void *(*copy)(), void (*destroy)());

int why_vector_reallocate(why_vector *vector, int extra_item_capacity);

void *why_vector_at(const why_vector *vector, int index);
void *why_vector_pop(why_vector *vector);
void *why_vector_replace_at(why_vector *vector, const void *item, int index); //returns the old item

int why_vector_push(why_vector *vector, const void *item);
int why_vector_get_length(const why_vector *vector);
int why_vector_is_sorted(const why_vector *vector, int (*comapre)());
int why_vector_swap(why_vector *vector, int j, int k);

void why_vector_destroy(why_vector **vector);


#endif