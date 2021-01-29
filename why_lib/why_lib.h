#ifndef WHY_LIB_H
#define WHY_LIB_H

typedef struct why_buffer why_buffer;
typedef struct why_vector why_vector;
typedef struct why_list why_list;
typedef struct why_list_item why_list_item;
typedef struct why_hash_table why_hash_table;
typedef struct why_matcher why_matcher;
typedef why_vector why_stack;
typedef why_list why_queue;

#include "headers/why_string.h"
#include "headers/why_display.h"


#define DEFAULT 0

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
int why_vector_nullify(why_vector *vector);

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
void *why_vector_accumualte(const why_vector *vector, int start, int number_of_items, char *(*combine)());

//math
unsigned int why_math_random(unsigned int seed, unsigned int max);

//hash
unsigned int why_hash_string(const char *string, unsigned int table_size);
why_hash_table *why_hash_table_create(unsigned int size, unsigned int (*hash_function)(), void *(*copy)(), void (*destroy)());
int why_hash_table_add(why_hash_table *table, void *item);
void *why_hash_table_search(why_hash_table *table, void *item, int (*compare)());
void why_hash_table_apply(why_hash_table *table, void (*top_function)(), void (*bottom_function)());
void why_hash_table_destroy(why_hash_table **table);

void **why_hash_table_get_table(const why_hash_table *table); // this is bad;
unsigned int why_hash_table_get_size(const why_hash_table *table); //

//matcher

why_matcher *why_matcher_create(const char *string);

int why_matcher_get_token_length(const why_matcher *matcher);
int why_matcher_get_min_pattern_length(const why_matcher *matcher);

//
int match_and_count(char *string, char *pattern);
int match_and_count_mk2(why_matcher *matcher, char *pattern);
// char *why_matcher_next(why_matcher *matcher, char *pattern);
//

char *why_matcher_get_matching_substring(why_matcher *matcher, char *pattern);

void why_matcher_destroy(why_matcher **matcher);

//print

char *why_string_get_formatted_string(const char *format, ...);

#endif