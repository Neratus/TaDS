#include "static_queue.h"
#include "dynamic_queue.h"
#include "list_queue.h"
#include "simulate_queue.h"
#include "test.h"
#include "func.h"


#define MAX_STR_LEN 200

int main(void)
{
    char input[MAX_STR_LEN];
    static_queue_t static_queue = init_static();
    dynamic_queue_t dynamic_queue = init_dynamic();
    list_queue_t *list_queue = init_list();
    printf("Программа,для работы с очередью,выполняющую операции добавления, удаления элементов и вывод текущего состояния очереди.\n");
    printf("Очередь реализоваан в виде статического массива, динамического массива и списка\n");
    printf("Программа позволяет проводить имитацию работы системы обработки заявок с использованием различных типов очередей\n");
    printf("Выберите опцию:\n");
    printf("СТАТИЧЕСКИЙ МАССИВ: \n");
    printf("\t1  - Добавить число в очередь \n");
    printf("\t2  - Удалить число из очереди \n");
    printf("\t3  - Вывести состояние очереди \n");
    printf("\t4  - Запустить симуляцию \n");
    printf("ДИНАМИЧЕСКИЙ МАССИВ: \n");
    printf("\t5  - Добавить число в очередь \n");
    printf("\t6  - Удалить число из очереди \n");
    printf("\t7  - Вывести состояние очереди \n");
    printf("\t8  - Запустить симуляцию \n");
    printf("СПИСОК: \n");
    printf("\t9  - Добавить число в очередь \n");
    printf("\t10 - Удалить число из очереди \n");
    printf("\t11 - Вывести состояние очереди \n");
    printf("\t12 - Запустить симуляцию \n");
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
            printf("Введите число для добавления: ");
            double cur = 0;
            if (scanf("%lf",&cur) == 1)
            {
                if (queue_static_push(&static_queue, cur) != OK)
                    printf("ERROR: Превышен максимально допустимый размер буфера \n");
                else
                    printf("Добавление успешно \n");
            }
            else
                printf("Ошибка чтения \n");
        }
        else if (current_option == 2)
        {
            double cur = queue_static_pop(&static_queue);
            if (isnan(cur))
                printf("ERROR: стек пуст \n \n");
            else
                printf("Удаление элемета %lf успешно \n", cur);
        }
        else if (current_option == 3)
            queue_static_current(static_queue);
        else if (current_option == 4)
            simulate_static();
        else if (current_option == 5)
        {
            printf("Введите число для добавления: ");
            double cur = 0;
            if (scanf("%lf",&cur) == 1)
            {
                if (queue_dynamic_push(&dynamic_queue, cur) != OK)
                    printf("ERROR: Ошибка добавления \n");
                else
                    printf("Добавление успешно \n");
            }
            else
                printf("Ошибка чтения \n");
        }
        else if (current_option == 6)
        {
            double cur = queue_dynamic_pop(&dynamic_queue);
            if (isnan(cur))
                printf("ERROR: стек пуст \n \n");
            else
                printf("Удаление элемета %lf успешно \n", cur);
        }
        else if (current_option == 7)
            queue_dynamic_current(dynamic_queue);
        else if (current_option == 8)
            simulate_dynamic();
        else if (current_option == 9)
        {
            printf("Введите число для добавления: ");
            double cur = 0;
            if (scanf("%lf",&cur) == 1)
            {
                if (queue_list_push(list_queue, cur) != OK)
                    printf("ERROR: Ошибка добавления \n");
                else
                    printf("Добавление успешно \n");
            }
            else
                printf("Ошибка чтения \n");
        }
        else if (current_option == 10)
        {
            double cur = queue_list_pop(list_queue);
            if (isnan(cur))
                printf("ERROR: стек пуст \n \n");
            else
                printf("Удаление элемета %lf успешно \n", cur);
        }
        else if (current_option == 11)
            queue_list_current(list_queue);
        else if (current_option == 12)
            simulate_list();
        else if (current_option == 13)
            test_queue();
        else if (current_option == 14)
        {
            printf("СТАТИЧЕСКИЙ МАССИВ: \n");
            printf("\t1  - Добавить число в очередь \n");
            printf("\t2  - Удалить число из очереди \n");
            printf("\t3  - Вывести состояние очереди \n");
            printf("\t4  - Запустить симуляцию \n");
            printf("ДИНАМИЧЕСКИЙ МАССИВ: \n");
            printf("\t5  - Добавить число в очередь \n");
            printf("\t6  - Удалить число из очереди \n");
            printf("\t7  - Вывести состояние очереди \n");
            printf("\t8  - Запустить симуляцию \n");
            printf("СПИСОК: \n");
            printf("\t9  - Добавить число в очередь \n");
            printf("\t10 - Удалить число из очереди \n");
            printf("\t11 - Вывести состояние очереди \n");
            printf("\t12 - Запустить симуляцию \n");
            printf("13 - Замер производительности \n");
            printf("14 - Вывод доступных опций \n");
            printf(" 0 - Завершение работы..... \n");
        }
        else if (current_option == 0)
        {
            printf("Завершение работы \n");
            if (dynamic_queue.array != NULL)
                free_dynamic(&dynamic_queue);
            if (queue_list_is_empty(*list_queue) == 0)
            {
                free_adress();
                free_list(list_queue);
            }
            return OK;
        }
        else
            printf("Недопустимая опция, пожалуйста повторите  \n");
        printf("Выберите опцию:\n");
        printf("Опция: ");
    }
    free_dynamic(&dynamic_queue);
    free_adress();
    free_list(list_queue);
    printf("Завершение работы \n");
    return OK;
}
