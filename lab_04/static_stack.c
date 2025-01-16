#include "static_stack.h"


int stack_static_size(static_stack_t stack)
{
     return stack.index_cur;
}

void stack_static_current(static_stack_t stack)
{
    printf("Длина стека: %d \n", stack_static_size(stack));
    printf("Элементы стека: ");
    for (size_t i = 0; i < stack.index_cur; i++)
        printf("%c",stack.array[i]);
    printf("\n");
    
}

char stack_static_pop(static_stack_t *stack)
{
    if (stack->index_cur == 0)
        return ERROR_EMPTY;
    char cur = stack->array[--stack->index_cur];
    return cur;
}

int stack_static_push(static_stack_t *stack, char cur)
{
    if (stack->index_cur >= MAX_LEN)
        return ERROR_STACK_OVERFLOW;
    stack->index_cur++;
    stack->array[stack->index_cur - 1] = cur;
    return 0;
}


int stack_static_is_empty(static_stack_t stack)
{
    if (stack_static_size(stack) == 0)
        return 1;
    return 0;
}

void stack_static_copy(static_stack_t dest, static_stack_t source)
{
    dest.index_cur = source.index_cur;
    for (size_t i = 0; i < source.index_cur; i++)
        dest.array[i] = source.index_cur;
}

static_stack_t stack_static_init(void)
{
    static_stack_t stack;
    for (size_t i = 0; i < MAX_LEN; i++)
        stack.array[i] = 0;
    stack.index_cur = 0;
    return stack;
}

int check_string_stack_static(char *string, size_t str_len, size_t *size)
{
    static_stack_t stack = stack_static_init();

    if (str_len >= MAX_LEN)
    {
        printf("Превышен максимально допустимый размер буфера \n");
        return ERROR_STR_SIZE;
    }
    if (str_len == 0)
    {
        printf("Ошибка:введена пустая строка \n");
        return ERROR_EMPTY_STR;
    }
    for (size_t i = 0; i < str_len; i++)
        stack_static_push(&stack, string[i]);
    size_t get_size = sizeof(char) * stack.index_cur;
    *size = get_size;
    // for (size_t i = 0; i < str_len; i++)
    //     if (stack_static_pop(&stack) != string[i])
    //         return NO;
    return YES;
}

int polindrom_check_stack_static(void)
{
    static_stack_t stack = stack_static_init();
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
    if (len >= MAX_LEN)
    {
        printf("Превышен максимально допустимый размер буфера \n");
        return ERROR_STR_SIZE;
    }
    if (len == 0)
    {
        printf("Ошибка:введена пустая строка \n");
        return ERROR_EMPTY_STR;
    }
    for (size_t i = 0; i < len; i++)
        if (!isspace(line[i]))
            stack_static_push(&stack, line[i]);
    for (size_t i = 0; i < len; i++)
    {
        if (!isspace(line[i]))
            if (tolower(stack_static_pop(&stack)) != tolower(line[i]))
                return NO;
    }
    return YES;
}

