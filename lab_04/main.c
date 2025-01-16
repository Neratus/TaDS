#include "static_stack.h"
#include "dynamic_stack.h"
#include "list_stack.h"
#include "test_stack.h"
#include "func.h"

#define MAX_STR_LEN 200

int main(void)
{
    char input[MAX_STR_LEN];
    static_stack_t static_stack = stack_static_init();
    dynamic_stack_t dynamic_stack = stack_dynamic_init();
    list_stack_t *list_stack = stack_list_init();
    printf("Программа,для работы со стеком,выполняющую операции добавления, удаления элементов и вывод текущего состояния стека.\n");
    printf("Стек реализован в виде статического массива, динамического массива и списка\n");
    printf("Также программа способна осуществить проверку строки, является ли она палиндромом\n");
    printf("Выберите опцию:\n");
    printf("СТАТИЧЕСКИЙ МАССИВ: \n");
    printf("\t1  - Добавить символ в стек \n");
    printf("\t2  - Удалить символ из стека \n");
    printf("\t3  - Вывести состояние стека \n");
    printf("\t4  - Проверка введеной строки на палиндром с помощью стека \n");
    printf("ДИНАМИЧЕСКИЙ МАССИВ: \n");
    printf("\t5  - Добавить символ в стек \n");
    printf("\t6  - Удалить символ из стека \n");
    printf("\t7  - Вывести состояние стека \n");
    printf("\t8  - Проверка введеной строки на палиндром с помощью стека \n");
    printf("СПИСОК: \n");
    printf("\t9  - Добавить символ в стек \n");
    printf("\t10 - Удалить символ из стека \n");
    printf("\t11 - Вывести состояние стека \n");
    printf("\t12 - Проверка введеной строки на палиндром с помощью стека \n");
    printf("13 - Замер производительности \n");
    printf("14 - Вывод доступных опций \n");
    printf(" 0 - Завершение работы..... \n");
    printf("Опция: ");
    int current_option = 1;
    while(current_option != 0)
    {
        rewind(stdin);
        int rc = read_line(input, MAX_STR_LEN, stdin);
        char *end;
        current_option = strtol(input, &end, 10);
        if ((rc != OK) || (input == end))
        {
            rewind(stdin);
            current_option = -1;
        }
        if (current_option == 1)
        {
            printf("Введите символ: ");
            char ch = getchar();
            if (ch != EOF)
            {
                if (stack_static_push(&static_stack ,ch) != OK)
                    printf("ERROR: Превышен максимально допустимый размер буфера \n");
                else
                    printf("Добавление успешно \n");
            }
            else
                printf("Ошибка чтения \n");
        }
        else if (current_option == 2)
        {
            char ch = stack_static_pop(&static_stack);
            if (ch == -2)
                printf("ERROR: стек пуст \n \n");
            else
                printf("Удаление успешно \n");
        }
        else if (current_option == 3)
            stack_static_current(static_stack);
        else if (current_option == 4)
        {
            int res = polindrom_check_stack_static();
            if (res == YES)
                printf("Строка является палиндромом \n");
            else if (res == NO)
                printf("Строка НЕ является палиндромом \n");
            else
                printf("Не удалось проверить строку \n");
        }
        else if (current_option == 5)
        {
            printf("Введите символ: ");
            char ch = getchar();
            if (ch != EOF)
            {
                if (stack_dynamic_push(&dynamic_stack ,ch) != OK)
                    printf("ERROR:Превышен максимально допустимый размер буфера \n");
                else
                    printf("Добавление успешно \n");
            }
            else
                printf("Ошибка чтения \n");
        }
        else if (current_option == 6)
        {
            char ch = stack_dynamic_pop(&dynamic_stack);
            if (ch == -2)
                printf("ERROR:стек пуст \n \n");
            else
                printf("Удаление успешно \n");
        }
        else if (current_option == 7)
            stack_dynamic_current(dynamic_stack);
        else if (current_option == 8)
        {
            int res = polindrom_check_stack_dynamic();
            if (res == YES)
                printf("Строка является палиндромом \n");
            else if (res == NO)
                printf("Строка НЕ является палиндромом \n");
            else
                printf("Не удалось проверить строку \n");
        }
        else if (current_option == 9)
        {
            printf("Введите символ: ");
            char ch = getchar();
            if (ch != EOF)
            {
                if (stack_list_push(list_stack ,ch) != OK)
                    printf("ERROR: Превышен максимально допустимый размер буфера \n");
                else
                    printf("Добавление успешно \n");
            }
            else
                printf("Ошибка чтения \n");
        }
        else if (current_option == 10)
        {
            char ch = stack_list_pop(list_stack);
            if (ch == -2)
                printf("ERROR:стек пуст \n \n");
            else
                printf("Удаление успешно \n");
        }
        else if (current_option == 11)
            stack_list_current(*list_stack);
        else if (current_option == 12)
        {
            int res = polindrom_check_stack_list();
            if (res == YES)
                printf("Строка является палиндромом \n");
            else if (res == NO)
                printf("Строка НЕ является палиндромом \n");
            else
                printf("Не удалось проверить строку \n");
        }
        else if (current_option == 13)
            test_stack();
        else if (current_option == 14)
        {
            printf("СТАТИЧЕСКИЙ МАССИВ: \n");
            printf("\t1 - Добавить символ в статический стек \n");
            printf("\t2 - Удалить символ из статического стека \n");
            printf("\t3 - Вывести состояние стека \n");
            printf("\t4 - Проверка введеной строки на палиндром с помощью стека \n");
            printf("ДИНАМИЧЕСКИЙ МАССИВ: \n");
            printf("\t5 - Добавить символ в стек \n");
            printf("\t6 - Удалить символ из стека \n");
            printf("\t7 - Вывести состояние стека \n");
            printf("\t8 - Проверка введеной строки на палиндром с помощью стека \n");
            printf("СПИСОК: \n");
            printf("\t9  - Добавить символ в стек \n");
            printf("\t10 - Удалить символ из стека \n");
            printf("\t11 - Вывести состояние стека \n");
            printf("\t12 - Проверка введеной строки на палиндром с помощью стека \n");
            printf("13 - Замер производительности \n");
            printf("14 - Вывод доступных опций \n");
            printf(" 0 - Завершение работы..... \n");
        }
        else if (current_option == 0)
        {
            printf("Завершение работы \n");
            if (dynamic_stack.array != NULL)
                free(dynamic_stack.array);
            if (stack_list_is_empty(*list_stack) == 0)
            {
                free_adress();
                free_stack(list_stack);
            }
            return OK;
        }
        else
            printf("Недопустимая опция, пожалуйста повторите  \n");
        printf("Выберите опцию:\n");
        printf("Опция: ");
    }
    free(dynamic_stack.array);
    free_adress();
    free_stack(list_stack);
    printf("Завершение работы \n");
    return OK;
}
