#ifndef HASH_H
#define HASH_H

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
    int hash_1;
    int hash_2;
          
    // 1 = deleted
    //  2 = key
    int cell_state;
}Hash_node_t;

typedef struct
{
    Hash_node_t **table;
    int deleted_cnt;
    int keysCount;
    int table_size;
}Hash_table_t;

void init_hash_table(Hash_table_t *hash_table, int size);

void free_table(Hash_table_t *hash_table);

int add_elem_to_table(Hash_table_t **hash_table_ptr, char *key);

int delete_elem_from_table(Hash_table_t *hash_table, char *key);

void print_hash_table(Hash_table_t *hash_table);

int init_table_from_file(Hash_table_t **hash_table, char *filename);

Hash_node_t *find_node(Hash_table_t *hash_table, char *key, int *cmp_cnt);

void hash_delete_words_starting_with(Hash_table_t *hash_table, char letter, int *cmp_cnt);



#endif 
