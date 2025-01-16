#include "sort_student_keys.h"

void quick_sort_keys(key_t *keys, int len)
{
    int i = 0;
    int j = len - 1;
    char mid[FIELD_LEN];
    strncpy(mid,keys[len / 2].name,FIELD_LEN);
    do {
        while (strncmp(keys[i].name,mid,FIELD_LEN) < 0)
            i++;
        while (strncmp(keys[j].name,mid,FIELD_LEN) > 0)
            j--;
        if (i <= j) {
            key_t tmp = keys[i];
            keys[i] = keys[j];
            keys[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if(j > 0) 
        quick_sort_keys(keys, j + 1);
    if (i < len) 
        quick_sort_keys(&keys[i],len - i);
}


void bubble_sort_keys(key_t *keys, int len)
{
    for (int i = 0; i < len - 1; i++)
        for (int j = i; j < len; j++)
            if (strcmp(keys[i].name,keys[j].name) > 0)
            {
                key_t tmp = keys[i];
                keys[i] = keys[j];
                keys[j] = tmp;
            }
}

