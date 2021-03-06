#ifndef WHY_LIST_FUNCTIONS_H
#define WHY_LIST_FUNCTIONS_H

#include "why_typedefs.h"

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

#endif