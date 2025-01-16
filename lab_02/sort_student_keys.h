#ifndef SORT_KEYS_H
#define SORT_KEYS_H

#include "student.h"

typedef struct 
{
    short index;
    char name[FIELD_LEN + 1];
}key_t;


void quick_sort_keys(key_t *keys, int len);

void bubble_sort_keys(key_t *keys, int len);

#endif
