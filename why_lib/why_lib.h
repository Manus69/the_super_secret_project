#ifndef WHY_LIB_H
#define WHY_LIB_H


#include "headers/why_typedefs.h"
#include "headers/why_string.h"
#include "headers/why_display.h"

#define DEFAULT 0

//buffer
why_buffer *why_buffer_create(const char *file_name, int capacity, int read_size);

void why_buffer_destroy(why_buffer **buffer);

char *why_buffer_read_from(why_buffer *buffer, int number_of_bytes);

//file
void *why_file_read_all_lines_into_structure
(why_buffer *buffer, char terminator, void *structure, int (*push)());

char *why_file_read_file_into_string(const char *file_name);

why_vector *why_file_read_all_lines(const char *file_name);

//vector
why_vector *why_vector_create(int item_capacity, void *(*copy)(), void (*destroy)());

int why_vector_reallocate(why_vector *vector, int extra_item_capacity);

void *why_vector_at(const why_vector *vector, int index);
void *why_vector_pop(why_vector *vector);
void *why_vector_replace_at(why_vector *vector, const void *item, int index); //returns the old item
void *why_vector_apply_function_mk2(why_vector *vector, int (*function)(), int failure_value);

int why_vector_push(why_vector *vector, const void *item);
int why_vector_get_length(const why_vector *vector);
int why_vector_is_sorted(const why_vector *vector, int (*comapre)());
int why_vector_swap(why_vector *vector, int j, int k);
int why_vector_nullify(why_vector *vector);
int why_vector_apply_function(why_vector *vector, void (*function)());

void why_vector_destroy(why_vector **vector);
// void why_vector_content_destroy(void **content, int number_of_items, void (*destroy)());

//stack
why_stack *why_stack_create(int item_capacity, void *(*copy)(), void (*destroy)());

int why_stack_reallocate(why_stack *vector, int extra_item_capacity);

void *why_stack_pop(why_stack *vector);

int why_stack_push(why_stack *vector, const void *item);
int why_stack_get_length(const why_stack *vector);
int why_stack_is_sorted(const why_stack *vector, int (*comapre)());

//queue
why_queue *why_queue_create(void *(*copy)(), void (*destroy)());

int why_queue_get_length(const why_queue *queue);
int why_queue_enqueue(why_queue *queue, const void *content);

void *why_queue_dequeue(why_queue *queue);
void why_queue_destroy(why_queue **queue);

//list
why_list *why_list_create(void *(*copy)(), void (*destroy)());
why_list_item *why_list_get_head_iterator(const why_list *list);
why_list_item *why_list_get_tail_iterator(const why_list *list);
why_list_item *why_list_next(const why_list_item *list_item);
// why_list_item *get_iterator_at(const why_list *list, int index);

int why_list_get_length(const why_list *list);
int why_list_swap(why_list *list, int left_index, int right_index);
int why_list_push(why_list *list, const void *content);

void *why_list_pop(why_list *list);
void *why_list_dequeue(why_list *list);
void *why_list_get_content(const why_list_item *iterator);
void *why_list_at(const why_list *list, int index);
void *why_list_replace_at(why_list *list, const void *item, int index);
void *why_list_search(why_list *list, void *item, int (*comapre)());

void why_list_destroy(why_list **list);

//sort
void why_sort_array_heapsort(void **array, int size, int (*compare)());
void why_sort_vector_heapsort(why_vector *vector, int (*compare)());

void **why_sort_array_merge_mk2(void **array, int size, int (*compare)());
void **why_sort_array_merge(void **array, int number_of_items, int (*compare)());
void why_sort_vector_merge_mk2(why_vector *vector, int (*compare)());

void why_sort_array_insert(void **array, int left_index, int right_index, int (*compare)());
void why_sort_vector_insert(why_vector *vector, int (*compare)());

//accumulate
void *why_vector_accumualte(const why_vector *vector, int start, int number_of_items, void *(*combine)());

//math
unsigned int why_math_random(unsigned int seed, unsigned int max);

//hash
why_hash_table *why_hash_table_create(unsigned int size, unsigned int (*hash_function)(), void *(*copy)(), void (*destroy)());

unsigned int why_hash_string(const char *string, unsigned int table_size);
int why_hash_table_add(why_hash_table *table, void *item);

void *why_hash_table_search(why_hash_table *table, void *item, int (*compare)());

void why_hash_table_apply(why_hash_table *table, void (*top_function)(), void (*bottom_function)());
void why_hash_table_destroy(why_hash_table **table);

void **why_hash_table_get_table(const why_hash_table *table); // this is bad;
unsigned int why_hash_table_get_size(const why_hash_table *table); //

//matcher

why_matcher *why_matcher_create(const char *string);

char *why_matcher_get_next_match(why_matcher *matcher, char *pattern, int greedy, int inclusive);

int why_matcher_shift_position(why_matcher *matcher, int shift);

void why_matcher_reset(why_matcher *matcher, const char *string);
void why_matcher_destroy(why_matcher **matcher);

//print

// char *why_string_get_formatted_string(const char *format, va_arg *arg_list);

int why_print(const char *format, ... );

//conversions
// int why_string_itoa_buffer(int number, int base, char *buffer); //put this in a private header

//string buffer
why_string_buffer *why_string_buffer_create(int size);

char *why_string_buffer_get_content(const why_string_buffer *buffer);

void *why_string_buffer_write_string_rvp(why_string_buffer *buffer, const char *string);

int why_string_buffer_write_string(why_string_buffer *buffer, const char *string);
// int why_string_buffer_write_int(why_string_buffer *buffer, int number);
int why_string_buffer_check_capacity(why_string_buffer *buffer, int requirement);

void why_string_buffer_destory(why_string_buffer **buffer);

#endif