#ifndef STUDS_H
#define STUDS_H

#include "student.h"
#include <math.h>

#define MAX_FILE_CNT 2000
#define MIN_FILE_CNT 40

#define OK 0
#define ERROR_IO -1
#define ERROR_MAX_FILE_CNT -2
#define ERROR_MIN_FILE_CNT -3
#define ERROR_WRONG_OPTION -4
#define ERROR_ALL_DELETED -5
#define NO_ACCEPTABLE -6

int read_students_array_from_file(char *file_in, student_t students_to_add[MAX_FILE_CNT],int *cnt);

int add_student(student_t students_to_add[MAX_FILE_CNT],int *cnt);

int delete_student(student_t students[MAX_FILE_CNT],int *cnt);

int print_students_in_cheaper_rent(student_t students[MAX_FILE_CNT],int cnt);

#endif
