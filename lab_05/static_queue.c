#include "static_queue.h"

size_t queue_static_size(static_queue_t queue)
{
     return queue.size;
}

void queue_static_current(static_queue_t queue)
{
    printf("Длина очереди: %zu \n", queue_static_size(queue));
    printf("Элементы очереди: ");
    for (size_t i = 0; i < queue.size; i++) 
        printf("%lf ", queue.array[(queue.begin + i) % MAX_LEN]);
    printf("\n");
}

double queue_static_pop(static_queue_t *queue)
{
    if (queue->size == 0)
        return NAN;
    double cur = queue->array[queue->begin % MAX_LEN];
    queue->begin = (queue->begin + 1) % MAX_LEN;
    queue->size--;
    return cur;
}

int queue_static_push(static_queue_t *queue, double cur)
{
    if (queue->size >= MAX_LEN)
        return ERROR_STACK_OVERFLOW;
    queue->array[queue->end % MAX_LEN] = cur;
    queue->end = (queue->end + 1) % MAX_LEN;
    queue->size++;
    return 0;
}


int queue_static_is_empty(static_queue_t queue)
{
     return queue.size == 0;
}

void queue_static_copy(static_queue_t *dest, static_queue_t source)
{
    dest->begin = source.begin;
    dest->size = source.size;
    dest->end = source.end;
     for (size_t i = 0; i < source.size; i++) 
        dest->array[(source.begin + i) % MAX_LEN] = source.array[(source.begin + i) % MAX_LEN];
}


static_queue_t init_static(void)
{
    static_queue_t queue;
    queue.begin = 0;
    queue.end = 0;
    queue.size = 0;
    return queue;
}
