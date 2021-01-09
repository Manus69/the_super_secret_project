#ifndef WHY_DLIST_H
#define WHY_DLIST_H

#include "why_interfaces.h"

struct why_dlist
{
    why_interface *interface;

    struct why_dlist_item *head;
    struct why_dlist_item *tail;

    void *(*copy_function)();
    void (*content_destructor)();

    int length;
    int content_size;  
};

struct why_dlist_item
{
    void *content;

    why_dlist_item *left;
    why_dlist_item *right;
};

#endif