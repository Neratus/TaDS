#include "list_queue.h"

freed_adress_t *freed_adress = NULL;

int queue_list_size(list_queue_t queue)
{
    return queue.size;
}

int queue_list_is_empty(list_queue_t queue)
{
    return queue.size == 0;
}

list_queue_t *init_list(void)
{
    list_queue_t *list = malloc(sizeof(list_queue_t));
    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->allocated = 0;
    return list;
}

Node *create_nod(double cur)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return NULL;
    node->next = NULL;
    node->value = cur;
    return node;
}

void add_adress(Node *adress, size_t size, char operation)
{
    freed_adress_t *cur = malloc(sizeof(freed_adress_t));
    if (cur == NULL)
        return;
    cur->adress = adress;
    cur->size = size;
    cur->next = freed_adress;
    cur->operation = operation;
    freed_adress = cur;
}

int queue_list_push(list_queue_t *queue, double cur)
{
    Node *node = create_nod(cur);
    if (node == NULL)
        return ERROR_MALLOC;
    if (queue->tail == NULL)
        queue->head = node;
    else 
        queue->tail->next = node;
    queue->tail = node;
    queue->size++;
    queue->allocated++;
    add_adress(node, sizeof(Node), '+');
    return OK;
}

double queue_list_pop(list_queue_t *queue)
{
    if (queue->head == NULL)
        return NAN;
    Node *tmp = queue->head;
    double value = tmp->value;
    queue->head = tmp->next;
    if (queue->head == NULL) 
        queue->tail = NULL;
    add_adress(tmp, sizeof(Node), '-');
    free(tmp);
    queue->size--;
    return value;
}

void free_list(list_queue_t *queue)
{
    Node *cur = queue->head;
    Node *next;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    queue->size = 0;
    free(queue);
}

void free_adress(void)
{
    freed_adress_t *adr = freed_adress;
    freed_adress_t *next;
    while (adr)
    {
        next = adr->next;
        free(adr);
        adr = next;
    }
    freed_adress->size = 0;
    freed_adress = NULL;
}

void queue_list_current(list_queue_t *queue)
{
    printf("Длина стека: %zu \n", queue->size);
    printf("Элементы стека:\n");
    Node *cur = queue->head;
    int index = 0;
    while (cur)
    {
        printf("Элемент # %d : %lf \t Адрес: %p \n", index, cur->value, (void *)cur);
        index++;
        cur = cur->next;
    }
    printf("\n");
    printf("Аллоцированная память: %zu\n", queue->allocated * sizeof(double));
    printf("Память занятая элементами: %zu\n", queue->size * sizeof(double));
    printf("\n");
    if (freed_adress != NULL)
    {
        printf("Освобожденные зоны памяти: \n");
        freed_adress_t *adr = freed_adress;
        while (adr)
        {
            printf("Операция:%c Адрес %p:размер  %zu байт \n", adr->operation, (void *)adr->adress, adr->size);
            adr = adr->next;
        }
    }
}
