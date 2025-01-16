#include "sort_student_table.h"


void quick_sort_table(student_t *students, int len)
{
    int i = 0;
    int j = len - 1;
    char mid[FIELD_LEN];
    strncpy(mid,students[len/2].surname,FIELD_LEN);
    do {
        while (strncmp(students[i].surname,mid,FIELD_LEN) < 0)
            i++;
        while (strncmp(students[j].surname,mid,FIELD_LEN) > 0)
            j--;
        if (i <= j) {
            student_t tmp = students[i];
            students[i] = students[j];
            students[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if(j > 0) 
        quick_sort_table(students, j + 1);
    if (i < len) 
        quick_sort_table(&students[i], len - i);
}


void bubble_sort_table(student_t *students, int len)
{
    for (int i = 0; i < len - 1; i++)
        for (int j = i; j < len; j++)
            if (strcmp(students[i].surname,students[j].surname) > 0)
            {
                student_t tmp = students[i];
                students[i] = students[j];
                students[j] = tmp;
            }
}
