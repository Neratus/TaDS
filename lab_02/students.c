#include "students.h"


int read_students_array_from_file(char *file_in, student_t students_to_add[MAX_FILE_CNT],int *cnt)
{
    FILE *f = fopen(file_in,"r");
    int a = 0;
    if (f == NULL)
        return ERROR_IO;
    char str[MAX_STR_LEN + 1];
    int rc = read_line(str, MAX_STR_LEN, f);
    while (rc == OK)
    {
        student_t std;
        rc = check_student(str,&std);
        if (rc != OK)
        {
            fclose(f);
            *cnt = a++;
            return rc;
        }
        if (a >= MAX_FILE_CNT)
        {
            *cnt = a;
            fclose(f);
            return ERROR_MAX_FILE_CNT;
        }
        students_to_add[a] = std;
        a++;
        rc = read_line(str, MAX_STR_LEN, f);
    }
    fclose(f);
    *cnt = a;
    if (rc == ERROR_STR_INPUT)
        return OK;
    return rc;
}

int add_student(student_t students_to_add[MAX_FILE_CNT],int *cnt)
{
    char str[MAX_STR_LEN + 1];
    int a = *cnt;
    int rc = read_line(str, MAX_STR_LEN, stdin);
    if (rc != OK)
        return rc;
    student_t std;
    rc = check_student(str,&std);
    if (rc != OK)
        return rc;
    if (a + 1 >= MAX_FILE_CNT)
        return ERROR_MAX_FILE_CNT;
    a++;
    students_to_add[a - 1] = std;
    *cnt = a;
    return OK;
}

void remove_student_from_array(student_t students[MAX_FILE_CNT],int index, int *cnt)
{
    int a = *cnt;
    for (int j = index; j < a - 1; j++) 
        students[j] = students[j + 1];
    a--;
    *cnt = a;
}

int delete_student(student_t students[MAX_FILE_CNT],int *cnt)
{
    printf("Выберите поле для удаления \n");
    printf("1 - Фамилия студента\n");
    printf("2 - Имя студента\n");
    printf("3 - Группа студента\n");
    printf("4 - Пол студента\n");
    printf("5 - Возраст студента\n");
    printf("6 - Балл студента\n");
    printf("7 - Дата принятия\n");
    printf("8 - Тип жилья\n");
    printf("9 - Сравнение по типу жилья\n");
    int option;
    int len = *cnt;
    char str[FIELD_LEN + 1];
    if ((scanf("%d", &option) != 1) || (option < 1) || (option > 9))
        return ERROR_WRONG_OPTION;
    rewind(stdin);
    if (option == 1)
    {
        printf("Введите фамилию студента: ");
        int rc = read_line(str, FIELD_LEN, stdin);
        if (rc != OK)
            return rc;
        rc = check_str_for_latin_symbols(str);
        if (rc != VALID)
            return rc;
        int cur = 0;
        while (cur < len)
        {
            if (strcmp(students[cur].surname,str) == 0)
                remove_student_from_array(students,cur,&len);
            else
                cur++;
        }
        *cnt = len;
        if (cur == 0)
            return ERROR_ALL_DELETED;
        return OK;
    }
    if (option == 2)
    {
        printf("Введите имя студента: ");
        int rc = read_line(str, FIELD_LEN, stdin);
        if (rc != OK)
            return rc;
        rc = check_str_for_latin_symbols(str);
        if (rc != VALID)
            return rc;
        int cur = 0;
        while (cur < len)
        {
            if (strcmp(students[cur].name,str) == 0)
                remove_student_from_array(students,cur,&len);
            else
                cur++;
        }
        *cnt = len;
        if (cur == 0)
            return ERROR_ALL_DELETED;
        return OK;
    }
    if (option == 3)
    {
        printf("Введите группу студента: ");
        int rc = read_line(str, FIELD_LEN, stdin);
        if (rc != OK)
            return rc;
        int cur = 0;
        while (cur < len)
        {
            if (strcmp(students[cur].group,str) == 0)
                remove_student_from_array(students,cur,&len);
            else
                cur++;
        }
        *cnt = len;
        if (cur == 0)
            return ERROR_ALL_DELETED;
        return OK;
    }
    if (option == 4)
    {
        printf("Введите пол студента: ");
        char required;
        if ((scanf("%c",&required) != 1) || ((required != 'm') && (required != 'f')))
            return NOT_VALID;
        int cur = 0;
        while (cur < len)
        {
            printf("%c %c\n",required,students[cur].gender);
            if (required == students[cur].gender)
                remove_student_from_array(students,cur,&len);
            else
                cur++;
        }
        *cnt = len;
        if (cur == 0)
            return ERROR_ALL_DELETED;
        return OK;
    }
    if (option == 5)
    {
        printf("Введите возраст студента: ");
        int required;
        if ((scanf("%d",&required) != 1) || (required <= 0) || (required > 120))
            return NOT_VALID;
        int cur = 0;
        while (cur < len)
        {
            if (required == students[cur].age)
                remove_student_from_array(students,cur,&len);
            else
                cur++;
        }
        *cnt = len;
        if (cur == 0)
            return ERROR_ALL_DELETED;
        return OK;
    }
    if (option == 6)
    {
        printf("Введите средний балл студента: ");
        double required;
        if ((scanf("%lf",&required) != 1) || (required <= 0) || (required > 100))
            return NOT_VALID;
        int cur = 0;
        while (cur < len)
        {
            if (fabs(required - students[cur].aver_score) < 1e-8)
                remove_student_from_array(students,cur,&len);
            else
                cur++;
        }
        *cnt = len;
        if (cur == 0)
            return ERROR_ALL_DELETED;
        return OK;
    }
    if (option == 7)
    {
        int admition[DATE_CNT];
        printf("Введите дату зачисления студента: ");
        int rc = read_line(str, FIELD_LEN, stdin);
        if (rc != OK)
            return rc;
        rc = check_date(str, 1940, 2024, admition);
        if (rc != VALID)
            return rc;
        int cur = 0;
        while (cur < len)
        {
            if ((admition[0] == students[cur].admission_date[0]) && (admition[1] == students[cur].admission_date[1]) && (admition[2] == students[cur].admission_date[2]))
                remove_student_from_array(students,cur,&len);
            else
                cur++;
        }
        *cnt = len;
        if (cur == 0)
            return ERROR_ALL_DELETED;
        return OK;
    }
    if (option == 8)
    {
        printf("Введите тип жилья студента: ");
        int required;
        if ((scanf("%d",&required) != 1) || (required <= 0) || (required > 3))
            return NOT_VALID;
        int cur = 0;
        while (cur < len)
        {
            if (required == students[cur].housing_type_index)
                remove_student_from_array(students,cur,&len);
            else
                cur++;
        }
        *cnt = len;
        if (cur == 0)
            return ERROR_ALL_DELETED;
        return OK;
    }
    else
    {
        printf("Выберите тип жилья \n");
        printf("1 - Дом\n");
        printf("2 - Общежитие\n");
        printf("3 - Съемное жилье\n");
        if ((scanf("%d", &option) != 1) || (option < 1) || (option > 3))
            return ERROR_WRONG_OPTION;
        if (option == 1)
        {
            printf("Выберите требуемое поле \n");
            printf("1 - Улица\n");
            printf("2 - Номер дома\n");
            printf("3 - Номер квартиры\n");
            if ((scanf("%d", &option) != 1) || (option < 1) || (option > 3))
                return ERROR_WRONG_OPTION;
            if (option == 1)
            {
                printf("Введите улицу проживания студента: ");
                int rc = read_line(str, FIELD_LEN, stdin);
                if (rc != OK)
                    return rc;
                rc = check_str_for_latin_symbols(str);
                if (rc != VALID)
                    return rc;
                int cur = 0;
                while (cur < len)
                {
                    if ((students[cur].housing_type_index == 1) && (strcmp(students[cur].housing_type.house.street,str) == 0))
                        remove_student_from_array(students,cur,&len);
                    else
                        cur++;
                }
                *cnt = len;
                if (cur == 0)
                    return ERROR_ALL_DELETED;
                return OK;
            }
            else if (option == 2)
            {
                printf("Введите номер дома студента: ");
                int required;
                if ((scanf("%d",&required) != 1) || (required <= 0))
                    return NOT_VALID;
                int cur = 0;
                while (cur < len)
                {
                    if ((students[cur].housing_type_index == 1) && (required == students[cur].housing_type.house.house_num))
                        remove_student_from_array(students,cur,&len);
                    else
                        cur++;
                }
                *cnt = len;
                if (cur == 0)
                    return ERROR_ALL_DELETED;
                return OK;
            }
            else
            {
                printf("Введите номер квартиры студента: ");
                int required;
                if ((scanf("%d",&required) != 1) || (required <= 0))
                    return NOT_VALID;
                int cur = 0;
                while (cur < len)
                {
                    if ((students[cur].housing_type_index == 1) && (required == students[cur].housing_type.house.flat_num))
                        remove_student_from_array(students,cur,&len);
                    else
                        cur++;
                }
                *cnt = len;
                if (cur == 0)
                    return ERROR_ALL_DELETED;
                return OK;
            }
        }
        else if (option == 2)
        {
            printf("Выберите требуемое поле \n");
            printf("1 - Номер дома\n");
            printf("2 - Номер квартиры\n");
            if ((scanf("%d", &option) != 1) || (option < 1) || (option > 2))
                return ERROR_WRONG_OPTION;
            if (option == 1)
            {
                printf("Введите номер общежития студента: ");
                int required;
                if ((scanf("%d",&required) != 1) || (required <= 0))
                    return NOT_VALID;
                int cur = 0;
                while (cur < len)
                {
                    if ((students[cur].housing_type_index == 2) && (required == students[cur].housing_type.dormitory.dorm_num))
                        remove_student_from_array(students,cur,&len);
                    else
                        cur++;
                }
                *cnt = len;
                if (cur == 0)
                    return ERROR_ALL_DELETED;
                return OK;
            }
            else
            {
                printf("Введите номер квартиры студента: ");
                int required;
                if ((scanf("%d",&required) != 1) || (required <= 0))
                    return NOT_VALID;
                int cur = 0;
                while (cur < len)
                {
                    if ((students[cur].housing_type_index == 2) && (required == students[cur].housing_type.dormitory.room_num))
                        remove_student_from_array(students,cur,&len);
                    else
                        cur++;
                }
                *cnt = len;
                if (cur == 0)
                    return ERROR_ALL_DELETED;
                return OK;
            }
        }
        else
        {
            printf("Выберите требуемое поле \n");
            printf("1 - Улица\n");
            printf("2 - Номер дома\n");
            printf("3 - Номер квартиры\n");
            printf("4 - Стоимость\n");
            if ((scanf("%d", &option) != 1) || (option < 1) || (option > 4))
                return ERROR_WRONG_OPTION;
            if (option == 1)
            {
                printf("Введите улицу проживания студента: ");
                int rc = read_line(str, FIELD_LEN, stdin);
                if (rc != OK)
                    return rc;
                rc = check_str_for_latin_symbols(str);
                if (rc != VALID)
                    return rc;
                int cur = 0;
                while (cur < len)
                {
                    if ((students[cur].housing_type_index == 3) && (strcmp(students[cur].housing_type.rent_house.street,str) == 0))
                        remove_student_from_array(students,cur,&len);
                    else
                        cur++;
                }
                *cnt = len;
                if (cur == 0)
                    return ERROR_ALL_DELETED;
                return OK;
            }
            else if (option == 2)
            {
                printf("Введите номер дома студента: ");
                int required;
                if ((scanf("%d",&required) != 1) || (required <= 0))
                    return NOT_VALID;
                int cur = 0;
                while (cur < len)
                {
                    if ((students[cur].housing_type_index == 3) && (required == students[cur].housing_type.rent_house.house_num))
                        remove_student_from_array(students,cur,&len);
                    else
                        cur++;
                }
                *cnt = len;
                if (cur == 0)
                    return ERROR_ALL_DELETED;
                return OK;
            }
            else if (option == 3)
            {
                printf("Введите номер квартиры студента: ");
                int required;
                if ((scanf("%d",&required) != 1) || (required <= 0))
                    return NOT_VALID;
                int cur = 0;
                while (cur < len)
                {
                    if ((students[cur].housing_type_index == 3) && (required == students[cur].housing_type.rent_house.flat_num))
                        remove_student_from_array(students,cur,&len);
                    else
                        cur++;
                }
                *cnt = len;
                if (cur == 0)
                    return ERROR_ALL_DELETED;
                return OK;
            }
            else
            {
                printf("Введите цену квартиры студента: ");
                int required;
                if ((scanf("%d",&required) != 1) || (required <= 0))
                    return NOT_VALID;
                int cur = 0;
                while (cur < len)
                {
                    if ((students[cur].housing_type_index == 3) && (required == students[cur].housing_type.rent_house.price))
                        remove_student_from_array(students,cur,&len);
                    else
                        cur++;
                }
                *cnt = len;
                if (cur == 0)
                    return ERROR_ALL_DELETED;
                return OK;
            }
        }
    }
}

int print_students_in_cheaper_rent(student_t students[MAX_FILE_CNT],int cnt)
{
    rewind(stdin);
    int printed = 0;
    printf("Введите год зачисления студента: ");
    int year;
    if ((scanf("%d",&year) != 1) || (year < 1940) || (year > 2024))
        return NOT_VALID;
    printf("Введите цену квартиры студента: ");
    int price;
    if ((scanf("%d",&price) != 1) || (price <= 0))
        return NOT_VALID;
    for (int i = 0; i < cnt; i++)
    {
        if (year == students[i].admission_date[2])
            if ((students[i].housing_type_index == 3) && (students[i].housing_type.rent_house.price < price))
            {
                print_student(students[i],stdout);
                printed++;
            }
    }
    if (printed == 0)
        return NO_ACCEPTABLE;
    return OK;
}
