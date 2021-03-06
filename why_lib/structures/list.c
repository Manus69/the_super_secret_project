#include "why_list_structure.h"
#include "why_list_functions.h"
#include "why_memory_functions.h"
#include "why_constants.h"

why_list *why_list_create(void *(*copy)(), void (*destroy)())
{
    why_list *list;

    if ((list = malloc(sizeof(why_list))))
    {
        list->head = NULL;
        list->tail = NULL;

        list->length = 0;

        list->copy_function = copy ? copy : why_memory_shallow_copy;
        list->content_destructor = destroy ? destroy : why_memory_destroy;

        return list;
    }

    return NULL;
}

static why_list_item *new_list_item(const why_list *list, const void *content)
{
    why_list_item *list_item;
    
    if (!(list_item = malloc(sizeof(why_list_item))))
        return NULL;

    list_item->content = list->copy_function(content);
    
    list_item->left = NULL;
    list_item->right = NULL;

    return list_item;
}

why_list_item *why_list_get_head_iterator(const why_list *list)
{
    return list ? list->head : NULL;
}

why_list_item *why_list_get_tail_iterator(const why_list *list)
{
    return list ? list->tail : NULL;
}

why_list_item *why_list_next(const why_list_item *list_item)
{
    return list_item ? list_item->right : NULL;
}

void why_list_destroy(why_list **list)
{
    why_list_item *iterator;
    why_list_item *next;
    void (*content_destructor)();

    if (!list || !*list)
        return ;

    content_destructor = (*list)->content_destructor;
    iterator = why_list_get_head_iterator(*list);

    while (iterator)
    {
        next = why_list_next(iterator);
        content_destructor(&iterator->content);
        why_memory_destroy((void **)&iterator);
        iterator = next;
    }
    why_memory_destroy((void **)list);
}

int why_list_get_length(const why_list *list)
{
    return list ? list->length : 0;
}

int why_list_push(why_list *list, const void *content)
{
    why_list_item *new_item;

    if (!list)
        return FAILURE;

    if (!(new_item = new_list_item(list, content)))
        return FAILURE;

    if (list->length == 0)
    {
        list->head = new_item;
    }
    else if (list->length == 1)
    {
        list->head->right = new_item;
        new_item->left = list->head;
        list->tail = new_item;
    }
    else
    {
        list->tail->right = new_item;
        new_item->left = list->tail;
        list->tail = new_item;
    }
    list->length ++;

    return SUCCESS;
}

void *why_list_pop(why_list *list)
{
    void *content;
    why_list_item *new_tail;

    if (!list || list->length == 0)
        return NULL;

    if (list->length == 1)
    {
        content = list->head->content;
        why_memory_destroy((void **)&list->head);
    }
    else if (list->length == 2)
    {
        content = list->tail->content;
        why_memory_destroy((void **)&list->tail);
        list->head->right = NULL;
    }
    else
    {
        content = list->tail->content;
        new_tail = list->tail->left;
        new_tail->right = NULL;
        why_memory_destroy((void **)&list->tail);
        list->tail = new_tail;
    }
    list->length --;

    return content;
}

void *why_list_dequeue(why_list *list)
{
    void *content;
    why_list_item *new_head;

    if (!list || list->length == 0)
        return NULL;
    
    content = list->head->content;
    if (list->length == 1)
    {
        why_memory_destroy((void **)&list->head);
    }
    else if (list->length == 2)
    {
        why_memory_destroy((void **)&list->head);
        list->head = list->tail;
        list->tail = NULL;
    }
    else
    {
        new_head = list->head->right;
        why_memory_destroy((void **)&list->head);
        list->head = new_head;
    }
    list->length --;

    return content;
}

void *why_list_get_content(const why_list_item *iterator)
{
    return iterator ? iterator->content : NULL;
}

why_list_item *get_iterator_at(const why_list *list, int index)
{
    why_list_item *iterator;

    iterator = list->head;
    while (index)
    {
        iterator = iterator->right;
        index --;
    }

    return iterator;
}

//unsafe
void *why_list_at(const why_list *list, int index)
{
    why_list_item *iterator;

    if (!list || index < 0)
        return NULL;
    
    iterator = get_iterator_at(list, index);

    return iterator->content;
}

void *why_list_replace_at(why_list *list, const void *item, int index)
{
    why_list_item *iterator;
    void *content;

    if (!list || index < 0)
        return NULL;

    iterator = get_iterator_at(list, index);
    content = iterator->content;
    iterator->content = list->copy_function(item);

    return content;
}

//this is very slow; dont use this
int why_list_swap(why_list *list, int left_index, int right_index)
{
    why_list_item *lhs;
    why_list_item *rhs;

    if (!list || left_index < 0 || right_index < 0)
        return FAILURE;
    
    if (left_index == right_index)
        return SUCCESS;
        
    lhs = get_iterator_at(list, left_index);
    rhs = get_iterator_at(list, right_index);
    why_memory_pointer_swap(&lhs->content, &rhs->content);

    return SUCCESS;
}

void *why_list_search(why_list *list, void *item, int (*comapre)())
{
    why_list_item *iterator;

    if (!list || !comapre)
        return NULL;

    iterator = why_list_get_head_iterator(list);
    while (iterator)
    {
        if (!comapre(iterator->content, item))
        {
            return iterator->content;
        }
        iterator = iterator->right;
    }

    return NULL;
}