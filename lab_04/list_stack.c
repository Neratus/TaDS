#include "list_stack.h"

freed_adress_t *freed_adress = NULL;

int stack_list_size(list_stack_t stack)
{
    return stack.size;
}

int stack_list_is_empty(list_stack_t stack)
{
    if (stack_list_size(stack) == 0)
        return 1;
    return 0;
}

list_stack_t *stack_list_init(void)
{
    list_stack_t *list = malloc(sizeof(list_stack_t));
    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->size = 0;
    list->allocated = 0;
    return list;
}

Node *create_nod(char cur)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return NULL;
    node->next = NULL;
    node->value = cur;
    return node;
}

void add_adress(Node *adress, size_t size)
{
    freed_adress_t *cur = malloc(sizeof(freed_adress_t));
    cur->adress = (char *)adress;
    cur->size = size;
    cur->next = freed_adress;
    freed_adress = cur;
}

int stack_list_push(list_stack_t *stack, char cur)
{
    Node *node = create_nod(cur);
    if (node == NULL)
        return ERROR_MALLOC;
    node->next = stack->head;
    stack->head = node;
    stack->size++;
    stack->allocated++;
    return OK;
}

char stack_list_pop(list_stack_t *stack)
{
    if ((stack == NULL) || (stack->head == NULL))
        return ERROR_EMPTY;
    Node *tmp = stack->head;
    stack->head = tmp->next;
    char value = tmp->value;
    add_adress(tmp, sizeof(Node));
    free(tmp);
    stack->size--;
    return value;
}

void free_stack(list_stack_t *stack)
{
    Node *cur = stack->head;
    Node *next;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    stack->size = 0;
    free(stack);
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
    free(freed_adress);
}

void stack_list_current(list_stack_t stack)
{
    printf("Длина стека: %d \n", stack_list_size(stack));
    printf("Элементы стека:\n");
    Node *cur = stack.head;
    int index = 0;
    while (cur)
    {
        printf("Элемент # %d : %c \t Адрес: %p \n", index, cur->value, (void *)cur);
        index++;
        cur = cur->next;
    }
    printf("\n");
    printf("Аллоцированная память: %zu\n", stack.allocated * sizeof(char));
    printf("Память занятая элементами: %zu\n", stack.size * sizeof(char));
    printf("\n");
    if (freed_adress != NULL)
    {
        printf("Освобожденные зоны памяти: \n");
        freed_adress_t *adr = freed_adress;
        while (adr)
        {
            printf("Адрес %p:размер  %zu байт \n", (void *)adr->adress, adr->size);
            adr = adr->next;
        }
    }
}

int check_string_stack_list(char *string, size_t str_len, size_t *size)
{
    list_stack_t *stack = stack_list_init();

    if (str_len == 0)
    {
        printf("Ошибка:введена пустая строка \n");
        return ERROR_EMPTY_STR;
    }
    for (size_t i = 0; i < str_len; i++)
        stack_list_push(stack, string[i]);
    size_t get_size = sizeof(Node) * stack->size;
    *size = get_size;

    // for (size_t i = 0; i < str_len; i++)
    //     if (stack_list_pop(stack) != string[i])
    //     {
    //         free_stack(stack);
    //         return NO;
    //     }
    free_stack(stack);
    return YES;
}

int polindrom_check_stack_list(void)
{
    list_stack_t *stack = stack_list_init();
    char line[MAX_LEN];
    size_t len = 0;
    printf("Введите требуемую строку, размер строки не должен превышать %d символов : ", MAX_LEN);
    int rc = read_line(line, MAX_LEN, stdin);
    len = strlen(line);
    if (rc != OK)
    {
        printf("Ошибка ввода строки \n");
        return ERROR_STR_INPUT;
    }
    if (len == 0)
    {
        printf("Ошибка:введена пустая строка \n");
        return ERROR_EMPTY_STR;
    }
    for (size_t i = 0; i < len; i++)
        if (!isspace(line[i]))
            stack_list_push(stack, line[i]);
    for (size_t i = 0; i < len; i++)
    {
        if (!isspace(line[i]))
            if (tolower(stack_list_pop(stack)) != tolower(line[i]))
            {
                free_stack(stack);
                return NO;
            }
    }
    free_stack(stack);
    return YES;
}
