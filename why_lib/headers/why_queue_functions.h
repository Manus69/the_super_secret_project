#ifndef WHY_QUEUE_FUNCTIONS_H
#define WHY_QUEUE_FUNCTIONS_H

#include "why_typedefs.h"

why_queue *why_queue_create(void *(*copy)(), void (*destroy)());

int why_queue_get_length(const why_queue *queue);
int why_queue_enqueue(why_queue *queue, const void *content);

void *why_queue_dequeue(why_queue *queue);
void why_queue_destroy(why_queue **queue);

#endif