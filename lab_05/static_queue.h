#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

#include "func.h"

#define MAX_LEN 10000


typedef struct
{
    double array[MAX_LEN];
    size_t begin;
    size_t end;
    size_t size;
}static_queue_t;

size_t queue_static_size(static_queue_t queue);

void queue_static_current(static_queue_t queue);

double queue_static_pop(static_queue_t *queue);

int queue_static_push(static_queue_t *queue, double cur);

int queue_static_is_empty(static_queue_t queue);

void queue_static_copy(static_queue_t *dest, static_queue_t source);

static_queue_t init_static(void);



#endif
