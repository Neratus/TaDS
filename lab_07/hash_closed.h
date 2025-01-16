#ifndef HASH_CLOSED__H
#define HASH_CLOSED__H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 200

#define OK 0
#define ERROR_NO_ELEM -1
#define ERROR_ALREADY_EXISTS -2
#define ERROR_MEMORY -3
#define ERROR_FILE -4

typedef struct
{
    char *key;
    int hash;
    void *next;
}Hash_closed_node_t;

typedef struct
{
    Hash_closed_node_t **table;
    int keysCount;
    int table_size;
}Hash_closed_table_t;

void init_closed_hash_table(Hash_closed_table_t *hash_table, int size);

void free_closed_table(Hash_closed_table_t *hash_table);

int add_elem_to_closed_table(Hash_closed_table_t **hash_table_ptr, char *key);

int delete_elem_from_closed_table(Hash_closed_table_t *hash_table, char *key);

void print_closed_hash_table(Hash_closed_table_t *hash_table);

int init_closed_table_from_file(Hash_closed_table_t **hash_table, char *filename);

Hash_closed_node_t *find_closed_node(Hash_closed_table_t *hash_table, char *key, int *cmp_cnt);

void closed_hash_delete_words_starting_with(Hash_closed_table_t *hash_table, char letter, int *cmp_cnt);



#endif 
