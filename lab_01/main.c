#include "float.h"
#include "float_division.h"
#include "print_interface.h"

#include <stdio.h>
#include <string.h>

#define ERROR_STR_INPUT -1
#define ERROR_STR_SIZE -2
#define ERROR_ORD_SIZE -3

static int read_line(char *str, size_t str_max)
{
    if (!fgets(str, str_max, stdin))
        return ERROR_STR_INPUT;
    char *p = strchr(str, '\n');
    if (p)
    {
        *p = 0;
        return 0;
    }
    return ERROR_STR_SIZE;
}

int main(void)
{
    char input[80];
    print_intro();
    print_input_annotation();
    int rc = read_line(input,81);
    if (rc != 0)
    {
        printf("ОШИБКА ПРИ ЧТЕНИИ СТРОКИ\n");
        return rc;
    }
    my_float_t first;
    rc = input_float(input,&first);
    if (rc != 0)
    {
        printf("ОШИБКА ПРИ ЧТЕНИИ ЧИСЛА\n");
        return rc;
    }
    // print_float(first);
    print_input_annotation();
    my_float_t second;
    rc = read_line(input,81);
    if (rc != 0)
    {
        printf("ОШИБКА ПРИ ЧТЕНИИ СТРОКИ\n");
        return rc;
    }
    rc = input_float(input,&second);
    if (rc != 0)
    {
        printf("ОШИБКА ПРИ ЧТЕНИИ ЧИСЛА\n");
        return rc;
    }
    // print_float(second);
    my_float_t result;
    rc = my_float_division(first,second,&result);
    if (rc == ERROR_ZERO_DIVISION)
    {
        printf("ОШИБКА ДЕЛЕНИЯ НА НОЛЬ\n");
        return rc;
    }
    round_up(&result);
    if ((result.order > 99999) || (result.order < -99999))
    {
        printf("ОШИБКА ПОРЯДКА ЧИСЛА \n");
        return ERROR_ORD_SIZE;
    }
    printf("Результат: \n");
    print_float(result);
    return 0;
}
