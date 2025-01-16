#ifndef STUD_H
#define STUD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FIELD_LEN 30
#define DATE_LEN 10
#define DATE_CNT 3
#define MAX_STR_LEN 200

#define VALID 0
#define NOT_VALID 1

#define OK 0

#define ERROR_WRONG_STR_LEN 2
#define ERROR_STR_INPUT 2
#define ERROR_STR_SIZE 3
#define ERROR_WORD_SIZE 4
#define ERROR_WRONG_ARG_CNT 5

typedef struct
{
    char surname[FIELD_LEN + 1];
    char name[FIELD_LEN + 1];
    char group[FIELD_LEN + 1];
    char gender;
    short age;
    double aver_score;
    short admission_date[DATE_CNT];
    short housing_type_index;
    union
    {
        struct
        {
            char street[FIELD_LEN + 1];
            int house_num;
            int flat_num;
        } house;
        struct
        {
            int dorm_num;
            int room_num;
        }dormitory;
        struct
        {
            char street[FIELD_LEN + 1];
            int house_num;
            int flat_num;
            int price;
        } rent_house;
    }housing_type;  
} student_t;

int read_line(char *str, size_t str_max, FILE *f);

int check_student(char *str,student_t *std);

void print_student(student_t student, FILE *f);

int check_str_for_latin_symbols(char *str);

int check_date(char *str, int min_year, int max_year, int date_arr[]);

#endif
