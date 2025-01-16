#include "dynamic_queue.h"

size_t queue_dynamic_size(dynamic_queue_t queue)
{
     return queue.size;
}

void queue_dynamic_current(dynamic_queue_t queue)
{
    printf("Длина очереди: %zu \n", queue_dynamic_size(queue));
    printf("Аллоцированная память: %zu\n",queue.allocated_memory );
    printf("Элементы очереди: ");
    for (size_t i = 0; i < queue.size; i++) 
        printf("%lf ", queue.array[(queue.begin + i) % queue.allocated_memory]);
    printf("\n");
}

int queue_dynamic_allocate(dynamic_queue_t *queue)
{
    size_t new_size = queue->allocated_memory * 2;
    double *new_array = realloc(queue->array, new_size * sizeof(double));
    if (new_array == NULL)
        return ERROR_MALLOC;
    queue->array = new_array;
    queue->allocated_memory = new_size;
    return OK;
}

double queue_dynamic_pop(dynamic_queue_t *queue)
{
   if (queue->size == 0)
        return NAN;
    double cur = queue->array[queue->begin % queue->allocated_memory];
    queue->begin = (queue->begin + 1) % queue->allocated_memory;
    queue->size--;
    return cur;
}

int queue_dynamic_push(dynamic_queue_t *queue, double cur)
{
    if (queue->size >= queue->allocated_memory - 1)
        if (queue_dynamic_allocate(queue) != OK)
            return ERROR_MALLOC;
    queue->array[queue->end] = cur;
    queue->end = (queue->end + 1) % queue->allocated_memory;
    queue->size++;
    return 0;
}

int queue_dynamic_is_empty(dynamic_queue_t queue)
{
    return queue.size == 0;
}

dynamic_queue_t init_dynamic(void)
{
    dynamic_queue_t queue;
    queue.allocated_memory = 2;
    queue.array = malloc(queue.allocated_memory * sizeof(double));
    if (queue.array == NULL)
        return queue;
    queue.size = 0;
    queue.begin = 0;
    queue.end = 0;
    return queue;
}

void free_dynamic(dynamic_queue_t *queue)
{
    free(queue->array);
    queue->array = NULL;
    queue->size = 0;
    queue->allocated_memory = 0;
    queue->begin = 0;
    queue->end = 0;
}
