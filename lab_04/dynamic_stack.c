#include "dynamic_stack.h"

int stack_dynamic_size(dynamic_stack_t stack)
{
     return stack.index_cur;
}

void stack_dynamic_current(dynamic_stack_t stack)
{
    printf("Длина стека: %d \n", stack_dynamic_size(stack));
    printf("Аллоцированная память: %zu\n",stack.allocated_memory );
    printf("Элементы стека: ");
    for (size_t i = 0; i < stack.index_cur; i++)
        printf("%c",stack.array[i]);
    printf("\n");
}

int stack_dynamic_allocate(dynamic_stack_t *stack)
{
    size_t new_size = stack->allocated_memory * 2;
    char *new_array = (char*) realloc(stack->array, new_size * sizeof(char));
    if (new_array == NULL)
        return ERROR_MALLOC;
    stack->array = new_array;
    stack->allocated_memory = new_size;
    return OK;
}

char stack_dynamic_pop(dynamic_stack_t *stack)
{
    if (stack->index_cur == 0)
        return ERROR_EMPTY;
    char cur = stack->array[--stack->index_cur];
    return cur;
}

int stack_dynamic_push(dynamic_stack_t *stack, char cur)
{
    if (stack->index_cur >= stack->allocated_memory)
        if (stack_dynamic_allocate(stack) != OK)
            return ERROR_MALLOC;
    stack->index_cur++;
    stack->array[stack->index_cur - 1] = cur;
    return 0;
}


int stack_dynamic_is_empty(dynamic_stack_t stack)
{
    if (stack_dynamic_size(stack) == 0)
        return 1;
    return 0;
}

dynamic_stack_t stack_dynamic_init(void)
{
    dynamic_stack_t stack;
    stack.allocated_memory = 2;
    stack.array = malloc(stack.allocated_memory * sizeof(char));
    if (stack.array == NULL)
        return stack;
    for (size_t i = 0; i < stack.allocated_memory; i++)
        stack.array[i] = 0;
    stack.index_cur = 0;
    return stack;
}

int check_string_stack_dynamic(char *string, size_t str_len, size_t *size)
{
    dynamic_stack_t stack = stack_dynamic_init();

    while (stack.allocated_memory < str_len)
    {
        if (stack_dynamic_allocate(&stack) != OK)
            return ERROR_MALLOC;
    }
    if (str_len == 0)
    {
        printf("Ошибка:введена пустая строка \n");
        return ERROR_EMPTY_STR;
    }
    for (size_t i = 0; i < str_len; i++)
        stack_dynamic_push(&stack, string[i]);
    size_t get_size = stack.index_cur * sizeof(char);
    *size = get_size;
    // for (size_t i = 0; i < str_len; i++)
    //     if (stack_dynamic_pop(&stack) != string[i])
    //         return NO;
    return YES;
}

int polindrom_check_stack_dynamic(void)
{
    dynamic_stack_t stack = stack_dynamic_init();
    char line[MAX_LEN];
    size_t len = 0;
    printf("Введите требуемую строку, размер строки не должен превышать %d символов : ",MAX_LEN);
    int rc = read_line(line, MAX_LEN, stdin);
    len = strlen(line);
    if (rc != OK)
    {
        printf("Ошибка ввода строки \n");
        return ERROR_STR_INPUT;
    }
    while (stack.allocated_memory < len)
    {
        if (stack_dynamic_allocate(&stack) != OK)
            return ERROR_MALLOC;
    }
    if (len == 0)
    {
        printf("Ошибка:введена пустая строка \n");
        return ERROR_EMPTY;
    }
    for (size_t i = 0; i < len; i++)
        if (!isspace(line[i]))
            stack_dynamic_push(&stack, line[i]);
    for (size_t i = 0; i < len; i++)
    {
        if (!isspace(line[i]))
            if (tolower(stack_dynamic_pop(&stack)) != tolower(line[i]))
                return NO;
    }
    return YES;
}
