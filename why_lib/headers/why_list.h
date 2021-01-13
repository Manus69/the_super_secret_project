#ifndef WHY_LIST_H
#define WHY_LIST_H

struct why_list
{
    struct why_list_item *head;
    struct why_list_item *tail;

    void *(*copy_function)();
    void (*content_destructor)();

    int length;
};

struct why_list_item
{
    void *content;

    why_list_item *left;
    why_list_item *right;
};

#endif