#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#include "func.h"


typedef struct
{
    double *array;
    size_t begin;
    size_t end;
    size_t size;
    size_t allocated_memory;
}
dynamic_queue_t;

size_t queue_dynamic_size(dynamic_queue_t queue);

void queue_dynamic_current(dynamic_queue_t queue);

double queue_dynamic_pop(dynamic_queue_t *queue);

int queue_dynamic_push(dynamic_queue_t *queue, double cur);

int queue_dynamic_is_empty(dynamic_queue_t queue);

dynamic_queue_t init_dynamic(void);

void free_dynamic(dynamic_queue_t *queue);


#endif 
