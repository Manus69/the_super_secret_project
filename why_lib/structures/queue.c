#include "why_lib.h"

why_queue *why_queue_create(void *(*copy)(), void (*destroy)())
{
    return why_list_create(copy, destroy);
}

int why_queue_get_length(const why_queue *queue)
{
    return why_list_get_length(queue);
}

int why_queue_enqueue(why_queue *queue, const void *content)
{
    return why_list_push(queue, content);
}

void *why_queue_dequeue(why_queue *queue)
{
    return why_list_pop(queue);
}

void why_queue_destroy(why_queue **queue)
{
    return why_list_destroy(queue);
}