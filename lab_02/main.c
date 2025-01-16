#include "student.h"
#include "students.h"
#include "sort_student_keys.h"
#include "sort_student_table.h"
#include "print_interface.h"
#include <time.h>

unsigned long long cur_time_nanosec(void)
{
    struct timespec val;
    clock_gettime(CLOCK_MONOTONIC_RAW,&val);
    return val.tv_nsec;
}

int main(void) 
{
    int current_option = 1;
    char input[MAX_STR_LEN];
    char file_path[MAX_STR_LEN];
    student_t students[MAX_FILE_CNT];
    key_t keys[MAX_FILE_CNT];
    int len = 0;
    int valid_file = 1;
    do
    {
        printf("\n");
        if (current_option == 1)
        {
            rewind(stdin);
            printf("Введите путь к файлу: \n");
            int rc = read_line(input, MAX_STR_LEN, stdin);
            if (rc == ERROR_STR_INPUT)
            {   
                printf("ERROR: Не удалось прочитать путь к файлу \n");
                return rc;
            }
            else if (rc == ERROR_STR_SIZE)
            {
                printf("ERROR: Путь к введеному файлу превысил максимальный размер буфера");
                return rc;
            }
            else
            {
                rc = read_students_array_from_file(input, students, &len);
                if (rc == ERROR_IO)
                    printf("ERROR: не удалось открыть файл\n");
                else if (rc == ERROR_STR_SIZE)
                    printf("ERROR: строка в файле превысила максиально допустимую длину в позиции %d \n",len);
                else if ((rc == ERROR_WRONG_STR_LEN) || (rc == ERROR_WORD_SIZE))
                    printf("ERROR: недопустимая длина слова в строке %d \n",len);
                else if (rc == ERROR_STR_INPUT)
                    printf("ERROR: не удалось прочитать строку № %d \n",len);
                else if (rc == ERROR_WRONG_ARG_CNT)
                    printf("ERROR: недопустимое количество аргументов в строке %d \n",len);
                else if (rc == NOT_VALID)
                    printf("ERROR: невалидное значение записи в строке %d \n",len);
                else if (len < MIN_FILE_CNT)
                    printf("ERROR: недостаточное количество записей в файле\n");
                else if (rc == ERROR_MAX_FILE_CNT)
                    printf("ERROR: количество записей превышает максмально допустимое\n");
                else
                {
                    printf("ФАЙЛ УСПЕШНО ПРОЧИТАН\n");
                    strcpy(file_path, input);
                    for (int i = 0; i < len; i++)
                    {
                        keys[i].index = i;
                        strncpy(keys[i].name, students[i].surname,FIELD_LEN + 1);
                    }               
                    valid_file = 0;
                }
            }
        }
        else if (current_option == 2)
        {
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else
            {
                int rc = add_student(students, &len);
                keys[len - 1].index = len - 1;
                strncpy(keys[len - 1].name, students[len - 1].surname,FIELD_LEN + 1);
                if (rc != OK)
                    printf("ОШИБКА ДОБАВЛЕНИЯ \n");
                else
                    printf("ДОБАВЛЕНИЕ УСПЕШНО \n");
            }
        }
        else if (current_option == 3)
        {
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else
            {
                int rc = delete_student(students,&len);
                for (int i = 0; i < len; i++)
                {
                    keys[i].index = i;
                    strncpy(keys[i].name, students[i].surname,FIELD_LEN + 1);
                }    
                if (rc != OK)
                    printf("ОШИБКА УДАЛЕНИЯ \n");
                else
                    printf("УДАЛЕНИЕ УСПЕШНО \n");
            }
        }
        else if (current_option == 4)
        {
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else
            {
                printf("Индекс ключа |   Фамилия         |    Имя         |     Группа       | Пол | Возраст |Средний балл|Дата поступления| Тип жилья| Информация о жилье| \n");
                printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
                for (int i = 0; i < len; i++)
                { 
                    printf("%-4d|\n", i + 1);
                    print_student(students[i],stdout);
                }
            }
        }
        else if (current_option == 5)
        {
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else
            {
                printf("Индекс ключа|Значение ключа|\n");
                for (int i = 0; i < len; i++)
                    printf("%-12d |%30s |\n",keys[i].index + 1,keys[i].name);
            }
        }
        else if (current_option == 6)
        {
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else
            {
                int rc = print_students_in_cheaper_rent(students,len);
                if (rc == NO_ACCEPTABLE)
                    printf("НЕТ ПОДХОДЯЩИХ \n");
                else if (rc != OK)
                    printf("ОШИБКА ПОИСКА \n");
            }
        }
        else if (current_option == 7)
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else 
            {
                bubble_sort_table(students,len);
                printf("СОРТИРОВКА ТАБЛИЦЫ СОРТИРОВКОЙ ПУЗЫРЬКОМ УСПЕШНА \n");
            }
        else if (current_option == 8)
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else 
            {
                quick_sort_table(students,len);
                printf("СОРТИРОВКА ТАБЛИЦЫ БЫСТРОЙ СОРТИРОВКОЙ УСПЕШНА \n");
            }
        else if (current_option == 9)
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else 
            {
                bubble_sort_keys(keys,len);
                printf("СОРТИРОВКА ТАБЛИЦЫ КЛЮЧЕЙ СОРТИРОВКОЙ ПУЗЫРЬКОМ УСПЕШНА \n");
            }
        else if (current_option == 10)
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else 
            {
                quick_sort_keys(keys,len);
                printf("СОРТИРОВКА ТАБЛИЦЫ КЛЮЧЕЙ БЫСТРОЙ СОРТИРОВКОЙ УСПЕШНА \n");
            }
        else if (current_option == 11)
        {
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else 
            {
                unsigned long long time_start,time_end;

                unsigned long long time_sort_table_quick = 0;
                double res_time_sort_table_quick = 0;

                unsigned long long time_sort_table_slow = 0;
                double res_time_sort_table_slow = 0;

                unsigned long long time_sort_keys_quick = 0;
                double res_time_sort_keys_quick = 0;

                unsigned long long time_sort_keys_slow = 0;
                double res_time_sort_keys_slow = 0;

                unsigned long long safe_lock = 0;
                size_t iter_cnt = 600 + 1;
                student_t temp[MAX_FILE_CNT];
                key_t temp_keys[MAX_FILE_CNT];
                int temp_len;
                for (size_t i = 0; i < iter_cnt; i++)
                {
                    read_students_array_from_file(input,temp,&temp_len);
                    time_start = cur_time_nanosec();
                    quick_sort_table(temp,len);
                    time_end = cur_time_nanosec();
                    if (safe_lock == 0)
                        safe_lock = time_end - time_start;
                    else if ((time_end - time_start) <= safe_lock * 10)
                        time_sort_table_quick += (time_end - time_start);
                    else
                        i--;
                }
                res_time_sort_table_quick = time_sort_table_quick / iter_cnt;
                safe_lock = 0;
                for (size_t i = 0; i < iter_cnt; i++)
                {
                    read_students_array_from_file(input,temp,&temp_len);
                    time_start = cur_time_nanosec();
                    bubble_sort_table(temp,len);
                    time_end = cur_time_nanosec();
                    if (safe_lock == 0)
                        safe_lock = time_end - time_start;
                    else if ((time_end - time_start) <= safe_lock * 10)
                        time_sort_table_slow += (time_end - time_start);
                    else
                        i--;
                }
                res_time_sort_table_slow = time_sort_table_slow / iter_cnt;
                safe_lock = 0;
                for (size_t i = 0; i < iter_cnt; i++)
                {
                    read_students_array_from_file(input,temp,&temp_len);
                    for (int i = 0; i < len; i++)
                    {
                        temp_keys[i].index = i;
                        strncpy(temp_keys[i].name, students[i].surname,FIELD_LEN + 1);
                    }  
                    time_start = cur_time_nanosec();
                    quick_sort_keys(temp_keys,len);
                    time_end = cur_time_nanosec();
                    if (safe_lock == 0)
                        safe_lock = time_end - time_start;
                    else if ((time_end - time_start) <= safe_lock * 10)
                        time_sort_keys_quick += (time_end - time_start);
                    else
                        i--;
                }
                res_time_sort_keys_quick = time_sort_keys_quick / iter_cnt;
                safe_lock = 0;
                for (size_t i = 0; i < iter_cnt; i++)
                {
                    read_students_array_from_file(input,temp,&temp_len);
                    for (int i = 0; i < len; i++)
                    {
                        temp_keys[i].index = i;
                        strncpy(temp_keys[i].name, students[i].surname,FIELD_LEN + 1);
                    }  
                    time_start = cur_time_nanosec();
                    bubble_sort_keys(temp_keys,len);
                    time_end = cur_time_nanosec();
                    if (safe_lock == 0)
                        safe_lock = time_end - time_start;
                    else if ((time_end - time_start) <= safe_lock * 10)
                        time_sort_keys_slow += (time_end - time_start);
                    else
                        i--;
                }
                res_time_sort_keys_slow = time_sort_keys_slow / iter_cnt;

                printf("ТЕСТИРОВАНИЕ СОРТИРОВКИ ЭЛЕМЕНТОВ НА %d ЭЛЕМЕНТОВ %zu ИТЕРАЦИЯМИ \n",len,iter_cnt);
                printf("--------------------------------------------------------------- \n");
                printf("Метод сортировки    |Сортировка таблиц|Cортировка ключей|\n");
                printf("Быстрая сортировка  |%17lf|%17lf|\n", res_time_sort_table_quick,res_time_sort_keys_quick);
                printf("Медленная сортировка|%17lf|%17lf|\n", res_time_sort_table_slow,res_time_sort_keys_slow);
                printf("--------------------------------------------------------------- \n");
                printf("Замер эффективности быстрой сортировки в процентах: %7lf \n",100*(res_time_sort_table_quick - (res_time_sort_keys_quick))/res_time_sort_table_quick);
                printf("Замер эффективности медленной сортировки в процентах: %7lf \n",100*(res_time_sort_table_slow - (res_time_sort_keys_slow))/res_time_sort_table_slow);
                printf("АНАЛИЗ ИСПОЛЬЗОВАННОЙ ПАМЯТИ:  \n");
                printf("Таблица данных: %zu \n",len * sizeof(student_t));
                printf("Таблица ключей: %zu \n",len * sizeof(int));
                printf("Общий объем: %zu \n",len * sizeof(student_t) + len * sizeof(int));
            }
        }
        else if (current_option == 12)
        {
            if (valid_file == 1)
                printf("Пожалуйста, инициализируйте файл(команда 1) перед обработкой файла \n");
            else
            {
                printf("Индекс ключа |   Фамилия         |    Имя         |     Группа       | Пол | Возраст |Средний балл|Дата поступления| Тип жилья| Информация о жилье| \n");
                printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
                for (int i = 0; i < len; i++)
                    print_student(students[keys[i].index],stdout);
            }
        }
        else
            printf("Недопустимая опция, пожалуйста повторите  \n");
        print_options();
        rewind(stdin);
        int rc = read_line(input, MAX_STR_LEN, stdin);
        char *end;
        current_option = strtol(input, &end, 10);
        if ((rc != OK) || (input == end))
        {
            rewind(stdin);
            current_option = -1;
        }
    }
    while (current_option != 0);
    printf("ЗАВЕРШЕНИЕ РАБОТЫ... \n");
    return 0;
}
