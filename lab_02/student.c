#include "student.h"

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

void print_student(student_t student, FILE *f)
{
    fprintf(f,"%12s |",student.surname);
    fprintf(f,"%12s |",student.name);
    fprintf(f,"%12s |",student.group);
    fprintf(f,"%1c |",student.gender);
    fprintf(f,"%3d |",student.age);
    fprintf(f,"%5.1lf |",student.aver_score);
    for (size_t i = 0; i < DATE_CNT - 1; i++)
        fprintf(f, "%2d.", student.admission_date[i]);
    fprintf(f, "%2d |", student.admission_date[DATE_CNT - 1]);
    fprintf(f,"%1d |",student.housing_type_index);
    if (student.housing_type_index == 1)
    {
        fprintf(f,"%s ",student.housing_type.house.street);
        fprintf(f,"%d ",student.housing_type.house.house_num);
        fprintf(f,"%d ",student.housing_type.house.flat_num);
    }
    if (student.housing_type_index == 2)
    {
        fprintf(f,"%d ",student.housing_type.dormitory.dorm_num);
        fprintf(f,"%d ",student.housing_type.dormitory.room_num);
    }
    if (student.housing_type_index == 3)
    {
        fprintf(f,"%s ",student.housing_type.rent_house.street);
        fprintf(f,"%d ",student.housing_type.rent_house.house_num);
        fprintf(f,"%d ",student.housing_type.rent_house.flat_num);
        fprintf(f,"%d ",student.housing_type.rent_house.price);
    }
    fprintf(f,"\n");
}

int split_str(char *str, char words[][FIELD_LEN + 1], size_t *words_cnt, char symb[])
{
    size_t a = 0;
    char *pword = strtok(str, symb);
    while (pword)
    {
        if (strlen(pword) > FIELD_LEN)
            return ERROR_WORD_SIZE;
        strcpy(words[a], pword);
        a++;
        pword = strtok(NULL, symb);
    }
    *words_cnt = a;
    return OK;
}

int check_str_for_latin_symbols(char *str)
{
    size_t str_len = strlen(str);
    for (size_t i = 0; i < str_len; i++)
    {
        if (!isalpha(str[i]))
            return NOT_VALID;
    }
    return VALID;
}

int check_date_value(long date, long month, long year)
{
    if ((date <= 0) || (year < 0))
        return NOT_VALID;
    const int month_dates[12] = { 31, 28, 31, 30, 31 ,30, 31, 31, 30, 31, 30, 31 };
    if ((month == 2) && (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)))
    {
        if (date > 29)
            return NOT_VALID;
        return VALID;
    }
    if (date > month_dates[month - 1])
            return NOT_VALID;
    return VALID;
}

int check_date(char *str, int min_year, int max_year, int date_arr[])
{
    size_t str_len = strlen(str);
    if ((str_len > DATE_LEN) || (str_len < DATE_LEN - 2))
        return NOT_VALID;
    size_t cnt = 0;
    char date[DATE_LEN / 2][FIELD_LEN + 1];
    int rc = split_str(str, date, &cnt, ".");
    if ((rc != OK) || (cnt != 3))
        return NOT_VALID;
    long day = strtol(date[0], NULL, 10);
    if ((day == 0) || ((date[0][0] == '+') || (day <= 0) || (day > 31)))
        return NOT_VALID;
    long month = strtol(date[1], NULL, 10);
    if ((month == 0) || ((date[1][0] == '+') || (month <= 0) || (month > 12)))
        return NOT_VALID;
    long year = strtol(date[2], NULL, 10);
    if ((year == 0) || ((date[2][0] == '+') || (year < min_year) || (year > max_year)))
        return NOT_VALID;
    date_arr[0] = day;
    date_arr[1] = month;
    date_arr[2] = year;
    return check_date_value(day, month, year);
}

int check_student(char *str,student_t *std)
{
    size_t cnt = 0;
    int admition[DATE_CNT];
    char words[MAX_STR_LEN / 2][FIELD_LEN + 1];
    int rc = split_str(str, words, &cnt, "\n \t");
    if (rc != OK)
        return rc;
    if ((cnt < 10) || (cnt > 12))
        return ERROR_WRONG_ARG_CNT;
    for (size_t i = 0; i < 2; i++)
    {
        rc = check_str_for_latin_symbols(words[i]);
        if (rc != VALID)
            return rc;
    }
    if ((strcmp(words[3],"f") != 0) && (strcmp(words[3],"m") != 0))
        return NOT_VALID;
    int age = -1;
    char *pend;
    age = strtol(words[4], &pend, 10);
    if ((pend == words[4]) || (age <= 0) || (age > 120))
        return NOT_VALID;
    double aver_score = -1;
    aver_score = strtof(words[5], &pend);
    if ((pend == words[5]) || (aver_score <= 0) || (aver_score > 100))
        return NOT_VALID;
    rc = check_date(words[6], 1940, 2024, admition);
    if (rc != VALID)
        return rc;
    int housing_type = -1;
    housing_type = strtol(words[7], &pend, 10);
    if ((pend == words[7]) || (housing_type <= 0) || (housing_type > 3))
        return NOT_VALID;
    if (housing_type == 1)
    {
        rc = check_str_for_latin_symbols(words[8]);
        if (rc != VALID)
            return rc;
        int house_num = -1;
        house_num = strtol(words[9], &pend, 10);
        if ((pend == words[9]) || (house_num <= 0))
            return NOT_VALID;
        int flat_num = -1;
        flat_num = strtol(words[10], &pend, 10);
        if ((pend == words[10]) || (flat_num <= 0))
            return NOT_VALID;
        strcpy(std->surname,words[0]);
        strcpy(std->name,words[1]);
        strcpy(std->group,words[2]);
        std->gender = words[3][0];
        std->age = age;
        std->aver_score = aver_score;
        memcpy(std->admission_date, admition, sizeof(admition));
        std->housing_type_index = housing_type;
        strcpy(std->housing_type.house.street,words[8]);
        std->housing_type.house.house_num = house_num;
        std->housing_type.house.flat_num = flat_num;
    }
    else if (housing_type == 2)
    {
        int dorm_num = -1;
        dorm_num = strtol(words[8], &pend, 10);
        if ((pend == words[8]) || (dorm_num <= 0))
            return NOT_VALID;
        int room_num = -1;
        room_num = strtol(words[9], &pend, 10);
        if ((pend == words[9]) || (room_num <= 0))
            return NOT_VALID;
        strcpy(std->surname,words[0]);
        strcpy(std->name,words[1]);
        strcpy(std->group,words[2]);
        std->gender = words[3][0];
        std->age = age;
        std->aver_score = aver_score;
        memcpy(std->admission_date, admition, sizeof(admition));
        std->housing_type_index = housing_type;
        std->housing_type.dormitory.dorm_num = dorm_num;
        std->housing_type.dormitory.room_num = room_num;
    }
    else
    {
        rc = check_str_for_latin_symbols(words[8]);
        if (rc != VALID)
            return rc;
        int house_num = -1;
        house_num = strtol(words[9], &pend, 10);
        if ((pend == words[9]) || (house_num <= 0))
            return NOT_VALID;
        int flat_num = -1;
        flat_num = strtol(words[10], &pend, 10);
        if ((pend == words[10]) || (flat_num <= 0))
            return NOT_VALID;
        int price = -1;
        price = strtol(words[10], &pend, 10);
        if ((pend == words[10]) || (price <= 0))
            return NOT_VALID;
        strcpy(std->surname,words[0]);
        strcpy(std->name,words[1]);
        strcpy(std->group,words[2]);
        std->gender = words[3][0];
        std->age = age;
        std->aver_score = aver_score;
        memcpy(std->admission_date, admition, sizeof(admition));
        std->housing_type_index = housing_type;
        strcpy(std->housing_type.rent_house.street,words[8]);
        std->housing_type.rent_house.house_num = house_num;
        std->housing_type.rent_house.flat_num = flat_num;
        std->housing_type.rent_house.price = price;
    }
    return OK;
}
