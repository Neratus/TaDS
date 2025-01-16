#include "multiply_matrix.h"
#include "full_matrix_input.h"
#include "sparse_matrix_input.h"
#include "generate_matrix.h"
#include "print_matrix.h"

#include <string.h>

#define MAX_STR_LEN 200

#define ERROR_STR_INPUT 1
#define ERROR_STR_SIZE 2

int read_line(char *str, size_t str_max, FILE *f)
{
    if (!fgets(str, str_max, f))
    {
        return ERROR_STR_INPUT;
    }
    char *p = strchr(str, '\n');
    if (p)
    {
        *p = 0;
        return OK;
    }
    return ERROR_STR_SIZE;
}


int main(void)
{
    full_matrix_t matrix_1;
    full_matrix_t matrix_2;
    int matrix_1_input = 0, matrix_2_input = 0;

    sparse_matrix_B_t first_sparse;
    size_t first_col = 0; size_t second_str = 0;
    sparse_matrix_A_t second_sparse;
    int first_sparse_input = 0, second_sparse_input = 0;

    sparse_matrix_B_t res;
    full_matrix_t res_1;

    int option = 1;
    int rc;
    printf("Цель программы: реализовать алгоритмы обработки разреженных матриц, сравнить\n");
    printf("эффективность использования этих алгоритмов со стандартными алгоритмами обработки матриц\n");
    printf("при различном процентном заполнении матриц ненулевыми значениями и при различных размерах матриц.\n");
    while (option != 0)
    {
        printf("Введите номер опции: \n");
        printf("1 - Ввести первую обычную матрицу\n");
        printf("2 - Ввести вторую обычную матрицу\n");
        printf("3 - Вывести первую обычную матрицу\n");
        printf("4 - Вывести вторую обычную матрицу\n");
        printf("5 - Ввести первую разряженную матрицу\n");
        printf("6 - Ввести вторую разряженную матрицу\n");
        printf("7 - Вывести первую разряженную матрицу\n");
        printf("8 - Вывести вторую разряженную матрицу\n");
        printf("9 - Произвести умножение обычных матриц\n");
        printf("10 -Произвести умножение разряженных матриц\n");
        printf("11 - Произвести измерение\n");
        printf("0 - Завершение работы\n");
        if (scanf("%d", &option) != 1) 
        {
            printf("Ошибка ввода опции\n");
            return ERROR_INPUT;;
        }
        if (option == 1)
        {
            printf("Выберите формат ввода матрицы: обычный(1), координатный(2) ");
            if (scanf("%d", &option) != 1) 
            {
                printf("Ошибка ввода опции\n");
                return ERROR_INPUT;;
            }
            if (option == 1)
            {
                printf("Выберите способ ввода матрицы: из консоли(1) или из файла(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    rc = input_matrix_standart_from_console(&matrix_1);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    matrix_1_input = 1;
                }
                else if (option == 2)
                {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = input_matrix_standart(path, &matrix_1);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    matrix_1_input = 1;
                }
                else 
                    printf("Недопустимая опция\n");

            }
            else if (option == 2)
            {
                printf("Выберите способ ввода матрицы: из консоли(1) или из файла(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    rc = input_matrix_coord_from_console(&matrix_1);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    matrix_1_input = 1;
                    
                }
                else if (option == 2)
                {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = input_matrix_coord(path, &matrix_1);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    matrix_1_input = 1;
                }
                else 
                    printf("Недопустимая опция\n");
            }
            else
                printf("Недопустимая опция\n");
        }
        else if (option == 2)
        {
            printf("Выберите формат ввода матрицы: обычный(1), координатный(2) ");
            if (scanf("%d", &option) != 1) 
            {
                printf("Ошибка ввода опции\n");
                return ERROR_INPUT;;
            }
            if (option == 1)
            {
                printf("Выберите способ ввода матрицы: из консоли(1) или из файла(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    rc = input_matrix_standart_from_console(&matrix_2);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    matrix_2_input = 1;
                    
                }
                else if (option == 2)
                {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = input_matrix_standart(path, &matrix_2);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    matrix_2_input = 1;
                }
                else 
                    printf("Недопустимая опция\n");

            }
            else if (option == 2)
            {
                printf("Выберите способ ввода матрицы: из консоли(1) или из файла(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    rc = input_matrix_coord_from_console(&matrix_2);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    matrix_2_input = 1;
                    
                }
                else if (option == 2)
                {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = input_matrix_coord(path, &matrix_2);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    matrix_2_input = 1;
                }
                else 
                    printf("Недопустимая опция\n");
            }
            else
                printf("Недопустимая опция\n");
        }
        else if (option == 3)
        {
            if (matrix_1_input == 0)
                printf("Ошибка: не введена первая матрица");
            else
            {
            printf("Выберите формат вывода матрицы: стандартный(1) или координатный(2) ");
            if (scanf("%d", &option) != 1) 
            {
                printf("Ошибка ввода опции\n");
                return ERROR_INPUT;
            }
            if (option == 1)
            {
                printf("Выберите способ вывода: в файл(1) или в консоль(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = print_matrix(path, matrix_1);
                    if (rc != OK)
                        printf("Произошла ошибка \n");
                }
                if (option == 2)
                    print_matrix_in_console(matrix_1);
                else 
                    printf("Недопустимая опция\n");
            }
            else if (option == 2)
            {
                printf("Выберите способ вывода: в файл(1) или в консоль(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = print_matrix_coord(path, matrix_1);
                    if (rc != OK)
                        printf("Произошла ошибка \n");
                }
                if (option == 2)
                    print_matrix_coord_in_console(matrix_1);
                else 
                    printf("Недопустимая опция\n");
                }
            else 
                printf("Недопустимая опция\n");
            }
        }
        else if (option == 4)
        {
             if (matrix_2_input == 0)
                printf("Ошибка: не введена первая матрица\n");
            else
            {
            printf("Выберите формат вывода матрицы: стандартный(1) или координатный(2) ");
            if (scanf("%d", &option) != 1) 
            {
                printf("Ошибка ввода опции\n");
                return ERROR_INPUT;
            }
            if (option == 1)
            {
                printf("Выберите способ вывода: в файл(1) или в консоль(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = print_matrix(path, matrix_2);
                    if (rc != OK)
                        printf("Произошла ошибка \n");
                }
                if (option == 2)
                    print_matrix_in_console(matrix_2);
                else 
                    printf("Недопустимая опция\n");
            }
            else if (option == 2)
            {
                printf("Выберите способ вывода: в файл(1) или в консоль(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = print_matrix_coord(path, matrix_2);
                    if (rc != OK)
                        printf("Произошла ошибка \n");
                }
                if (option == 2)
                    print_matrix_coord_in_console(matrix_2);
                else 
                    printf("Недопустимая опция\n");
                }
            else 
                printf("Недопустимая опция\n");
            }
        }
        else if (option == 5)
        {
            full_matrix_t prev;
            printf("ВВедите матрицу в координатном формате\n");
            printf("Выберите способ ввода матрицы: обычный(1) или координатный(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    printf("Выберите способ ввода матрицы: из консоли(1) или из файла(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                    {
                        rc = input_matrix_standart_from_console(&prev);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                        rc = input_sparse_matrix_B(prev, &first_sparse);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                            first_sparse_input = 1;
                            first_col = prev.m;
                        }
                        free(prev.data);
                        }
                    }
                    else if (option == 2)
                    {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = input_matrix_standart(path, &prev);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    else
                    {
                        rc = input_sparse_matrix_B(prev, &first_sparse);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                            first_col = prev.m;
                            first_sparse_input = 1;
                        }
                        free(prev.data);
                    }
                    }
                    else 
                        printf("Невалидная операция \n");
                }     
                else if (option == 2)
                {
                    printf("Выберите способ ввода матрицы: из консоли(1) или из файла(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                    {
                        rc = input_matrix_coord_from_console(&prev);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                        rc = input_sparse_matrix_B(prev, &first_sparse);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        first_col = prev.m;
                        free(prev.data);
                        first_sparse_input = 1;
                        }
                    }
                    else if (option == 2)
                    {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = input_matrix_coord(path, &prev);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    else
                    {
                        rc = input_sparse_matrix_B(prev, &first_sparse);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                        first_sparse_input = 1;
                        first_col = prev.m;
                        }
                        free(prev.data);
                    }
                    }
                    else 
                        printf("Невалидная опция\n");
                }
                else 
                    printf("Недопустимая опция\n");
            
        }
        else if (option == 6)
        {
            full_matrix_t prev;
            printf("ВВедите матрицу в координатном формате\n");
            printf("Выберите способ ввода матрицы: обычный(1) или координатный(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    printf("Выберите способ ввода матрицы: из консоли(1) или из файла(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                    {
                        rc = input_matrix_standart_from_console(&prev);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                        rc = input_sparse_matrix_A(prev, &second_sparse);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                            second_sparse_input = 1;
                            second_str = prev.n;
                        }
                        free(prev.data);
                        }
                    }
                    else if (option == 2)
                    {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = input_matrix_standart(path, &prev);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    else
                    {
                        rc = input_sparse_matrix_A(prev, &second_sparse);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                            second_sparse_input = 1;
                            second_str = prev.n;
                        }
                        free(prev.data);
                    }
                    }
                    else 
                        printf("Невалидная операция \n");
                }
                else if (option == 2)
                {
                    printf("Выберите способ ввода матрицы: из консоли(1) или из файла(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                    {
                        rc = input_matrix_coord_from_console(&prev);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                        rc = input_sparse_matrix_A(prev, &second_sparse);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");
                        else
                        {
                            second_sparse_input = 1;
                            second_str = prev.n;
                        }
                        free(prev.data);
                        }
                    }
                    else if (option == 2)
                    {
                    printf("Введите путь к файлу: ");
                    rewind(stdin);
                    char path[MAX_STR_LEN];
                    int rc = read_line(path, MAX_STR_LEN, stdin);
                    if (rc != OK)
                        return rc;
                    rc = input_matrix_coord(path, &prev);
                    if (rc != OK)
                        printf("Ошибка ввода матрицы \n");
                    else
                    {
                        rc = input_sparse_matrix_A(prev, &second_sparse);
                        if (rc != OK)
                            printf("Ошибка ввода матрицы \n");\
                        else
                        {
                            second_sparse_input = 1;
                            second_str = prev.n;
                        }
                        free(prev.data);
                    }
                    }
                    else 
                        printf("Невалидная опция\n");
                }
                else 
                    printf("Недопустимая опция\n");
        }
        else if (option == 7)
        {
            if (first_sparse_input == 1)
            {
                printf("Выберите формат вывода матрицы: стандартный(1) или координатный(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    printf("Выберите способ вывода матрицы: в консоль(1) или в файл(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                        print_sparse_matrix_B_standart_in_console(first_sparse);
                    else if (option == 2)
                    {
                        printf("Введите путь к файлу: ");
                        char path[MAX_STR_LEN];
                        rewind(stdin);
                        int rc = read_line(path, MAX_STR_LEN, stdin);
                        if (rc != OK)
                            return rc;
                        rc = print_sparse_matrix_B_standart(path, first_sparse);
                        if (rc != OK)
                            printf("Произошла ошибка \n");
                    }
                    else 
                        printf("Невалидная операция \n");
                    
                }
                else if (option == 2)
                {
                    printf("Выберите способ вывода матрицы: в консоль(1) или в файл(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                        print_sparse_matrix_B_coord_in_console(first_sparse);
                    else if (option == 2)
                    {
                        printf("Введите путь к файлу: ");
                        char path[MAX_STR_LEN];
                        rewind(stdin);
                        int rc = read_line(path, MAX_STR_LEN, stdin);
                        if (rc != OK)
                            return rc;
                        rc = print_sparse_matrix_B_coord(path, first_sparse);
                        if (rc != OK)
                            printf("Произошла ошибка \n");
                    }
                    else 
                        printf("Невалидная операция \n");
                    
                }
            }
            else
                printf("МАТРИЦА НЕ БЫЛА ВВЕДЕНА\n");
        }
        else if (option == 8)
        {
            if (second_sparse_input == 1)
            {
                printf("Выберите формат вывода матрицы: стандартный(1) или координатный(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    printf("Выберите способ вывода матрицы: в консоль(1) или в файл(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                        print_sparse_matrix_A_standart_in_console(second_sparse);
                    else if (option == 2)
                    {
                        printf("Введите путь к файлу: ");
                        char path[MAX_STR_LEN];
                        rewind(stdin);
                        int rc = read_line(path, MAX_STR_LEN, stdin);
                        if (rc != OK)
                            return rc;
                        rc = print_sparse_matrix_A_standart(path, second_sparse);
                        if (rc != OK)
                            printf("Произошла ошибка \n");
                    }
                    else 
                        printf("Невалидная операция \n");
                    
                }
                else if (option == 2)
                {
                    printf("Выберите способ вывода матрицы: в консоль(1) или в файл(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                        print_sparse_matrix_A_coord_in_console(second_sparse);
                    else if (option == 2)
                    {
                        printf("Введите путь к файлу: ");
                        char path[MAX_STR_LEN];
                        rewind(stdin);
                        int rc = read_line(path, MAX_STR_LEN, stdin);
                        if (rc != OK)
                            return rc;
                        rc = print_sparse_matrix_A_coord(path, second_sparse);
                        if (rc != OK)
                            printf("Произошла ошибка \n");
                    }
                    else 
                        printf("Невалидная операция \n");
                }
            }
            else
                printf("МАТРИЦА НЕ БЫЛА ВВЕДЕНА\n");
        }
        else if (option == 9)
        {
            if ((matrix_1_input == 1) && (matrix_2_input == 1))
            {
            int rc = mult_matrix(matrix_1, matrix_2, &res_1);
            if (rc != OK)
                printf("Ошибка умножения\n");
            else
            {
                printf("Выберите формат вывода матрицы: стандартный(1) или координатный(2) ");
                if (scanf("%d", &option) != 1) 
                {
                    printf("Ошибка ввода опции\n");
                    return ERROR_INPUT;
                }
                if (option == 1)
                {
                    printf("Выберите способ вывода: в файл(1) или в консоль(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                    {
                        printf("Введите путь к файлу: ");
                        rewind(stdin);
                        char path[MAX_STR_LEN];
                        int rc = read_line(path, MAX_STR_LEN, stdin);
                        if (rc != OK)
                            return rc;
                        rc = print_matrix(path, res_1);
                        if (rc != OK)
                            printf("Произошла ошибка \n");
                    }
                    if (option == 2)
                        print_matrix_in_console(res_1);
                    else 
                        printf("Недопустимая опция\n");
                }
                else if (option == 2)
                {
                    printf("Выберите способ вывода: в файл(1) или в консоль(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                    {
                        printf("Введите путь к файлу: ");
                        rewind(stdin);
                        char path[MAX_STR_LEN];
                        int rc = read_line(path, MAX_STR_LEN, stdin);
                        if (rc != OK)
                            return rc;
                        rc = print_matrix_coord(path, res_1);
                        if (rc != OK)
                            printf("Произошла ошибка \n");
                    }
                    if (option == 2)
                        print_matrix_coord_in_console(res_1);
                    else 
                        printf("Недопустимая опция\n");
                }
                else 
                    printf("Недопустимая опция\n");
                }
            }
            else 
                printf("МАТРИЦЫ НЕ БЫЛИ ВВЕДЕНЫ\n");
        }
        else if (option == 10)
        {
    
            if ((first_sparse_input == 1) && (second_sparse_input == 1))
            {
                if (second_str != first_col)
                {
                    printf("Ошибка умножения \n");
                    return ERROR_WRONG_MATR_SIZE;
                }
                int rc = multiply_matrix_sparse(first_sparse, second_sparse, &res);
            
                if (rc != OK)
                    printf("Ошибка умножения \n");
                else
                {
                    printf("Выберите формат вывода матрицы: стандартный(1) или координатный(2) ");
                    if (scanf("%d", &option) != 1) 
                    {
                        printf("Ошибка ввода опции\n");
                        return ERROR_INPUT;
                    }
                    if (option == 1)
                    {
                        printf("Выберите способ вывода матрицы: в консоль(1) или в файл(2) ");
                        if (scanf("%d", &option) != 1) 
                        {
                            printf("Ошибка ввода опции\n");
                            return ERROR_INPUT;
                        }
                        if (option == 1)
                            print_sparse_matrix_B_standart_in_console(res);
                        else if (option == 2)
                        {
                            printf("Введите путь к файлу: ");
                            char path[MAX_STR_LEN];
                            rewind(stdin);
                            int rc = read_line(path, MAX_STR_LEN, stdin);
                            if (rc != OK)
                                return rc;
                            rc = print_sparse_matrix_B_standart(path, res);
                            if (rc != OK)
                                printf("Произошла ошибка \n");
                        }
                        else 
                            printf("Невалидная операция \n");
                    }
                    else if (option == 2)
                    {
                        printf("Выберите способ вывода матрицы: в консоль(1) или в файл(2) ");
                        if (scanf("%d", &option) != 1) 
                        {
                            printf("Ошибка ввода опции\n");
                            return ERROR_INPUT;
                        }
                        if (option == 1)
                            print_sparse_matrix_B_coord_in_console(res);
                        else if (option == 2)
                        {
                            printf("Введите путь к файлу: ");
                            char path[MAX_STR_LEN];
                            rewind(stdin);
                            int rc = read_line(path, MAX_STR_LEN, stdin);
                            if (rc != OK)
                                return rc;
                            rc = print_sparse_matrix_B_coord(path, res);
                            if (rc != OK)
                                printf("Произошла ошибка \n");
                        }
                        else 
                            printf("Невалидная операция \n");
                    
                    }
                    else 
                        printf("Невалидная операция \n");
                }
            }
            else
                printf("МАТРИЦЫ НЕ БЫЛИ ВВЕДЕНЫ \n");
        }
        else if (option == 11)
            compare_matrix_operations();
        else if (option == 0)
            break;
        else
            printf("Недопустимая опция, пожалуйста повторите  \n");
        
    }
    if (matrix_1_input == 1)
        free(matrix_1.data);
    if (matrix_2_input == 1)
        free(matrix_2.data);
    if ((matrix_1_input == 1) && (matrix_2_input == 1))
        free(res_1.data);
    if (first_sparse_input == 1)
    {
        free(first_sparse.B);
        free(first_sparse.IB);
        free(first_sparse.JB);
    }
    if (second_sparse_input == 1)
    {
        free(second_sparse.A);
        free(second_sparse.IA);
        free(second_sparse.JA);
    }
    if ((first_sparse_input == 1) && (first_sparse_input == 1))
    {
        free(res.B);
        free(res.IB);
        free(res.JB);
    }
    return 0;
}
