#include "hash_closed.h"

double rehash_size_cl = 1.2;
int base_size_cl = 11;
double allocate_incr_cl = 1.5;


static int String_Hasher(char *key)
{
    int hash_value = 0;
    size_t length = strlen(key);
    
    for (size_t i = 0; i < length; i++)
        hash_value = (hash_value * 2 + key[i]);
    return hash_value;
}

int find_next_simple_cl(int cur)
{
    int next = cur + 1;
    int is_simple = 0;
    while (is_simple == 0)
    {
        int was = 0;
        for (int i = 2; i < (int)(next / 2); i++)
        {
            if (next % i == 0)
            {
                was = 1;
                break;
            } 
        }
        if (was == 0)
            return next;
        next++;
    }
    return next;
}


static Hash_closed_node_t *create_closed_hash_node(char *name)
{
    Hash_closed_node_t *node = malloc(sizeof(Hash_closed_node_t));
    if (node)
    {
        node->key = strdup(name);
        if (!node->key) 
        {
            free(node); 
            return NULL;
        }
        node->hash = String_Hasher(name);
        node->next = NULL;
    }
    return node;
}

static void free_closed_hash_node(Hash_closed_node_t *node)
{
    if (node)
    {
        free(node->key);
        free(node);
    }
}

void init_closed_hash_table(Hash_closed_table_t *hash_table, int size) 
{
    hash_table->table = malloc(size * sizeof(Hash_closed_node_t));
    for (int i = 0; i < size; i++) 
        hash_table->table[i] = NULL;
    hash_table->keysCount = 0;
    hash_table->table_size = size;
}

void free_closed_table(Hash_closed_table_t *hash_table)
{
    if (hash_table) 
    {
        if (hash_table->table)
        {
            for (int i = 0; i < hash_table->table_size; i++) 
            {
                Hash_closed_node_t *node = hash_table->table[i];
                while (node) 
                {
                    Hash_closed_node_t *temp = node;
                    node = node->next;
                    free_closed_hash_node(temp); 
                }
            }
            free(hash_table->table);
            hash_table->table = NULL;
        }
        free(hash_table); 
    }
}

static void rehash_closed_hash_table(Hash_closed_table_t **hash_table_ptr, int new_table_size) 
{
    Hash_closed_table_t *old_table = *hash_table_ptr; 
    Hash_closed_table_t *new_table = malloc(sizeof(Hash_closed_table_t));
    init_closed_hash_table(new_table, new_table_size);
    for (int i = 0; i < old_table->table_size; i++) 
    {
        if (old_table->table[i] != NULL) 
        {
            Hash_closed_node_t *node = old_table->table[i];
            
            while (node) 
            {
                int pos = String_Hasher(node->key) % new_table_size;

                Hash_closed_node_t *new_node = create_closed_hash_node(node->key);
                if (!new_node) 
                {
                    free_closed_table(new_table);
                    return;
                }

                new_node->next = new_table->table[pos];
                new_table->table[pos] = new_node;

                node = node->next;
            }

        }
    }
    new_table->keysCount = old_table->keysCount;
    free_closed_table(old_table);
    *hash_table_ptr = new_table;
}

int add_elem_to_closed_table(Hash_closed_table_t **hash_table_ptr, char *key)
{
    if ((*hash_table_ptr)->keysCount >= rehash_size_cl * (*hash_table_ptr)->table_size) 
        rehash_closed_hash_table(hash_table_ptr, find_next_simple_cl((int)(allocate_incr_cl *(*hash_table_ptr)->table_size)));

    int table_size = (*hash_table_ptr)->table_size;
    int hash = String_Hasher(key);  
    int index = hash % table_size; 

    Hash_closed_node_t *current = (*hash_table_ptr)->table[index];
    while (current != NULL) 
    {
        if (strcmp(current->key, key) == 0)
            return ERROR_ALREADY_EXISTS;
        current = current->next;
    }
    Hash_closed_node_t *new_node = create_closed_hash_node(key);
    if (!new_node) 
        return ERROR_MEMORY;

    new_node->next = (*hash_table_ptr)->table[index];
    (*hash_table_ptr)->table[index] = new_node;

    (*hash_table_ptr)->keysCount++;

    return OK;
}

int delete_elem_from_closed_table(Hash_closed_table_t *hash_table, char *key)
{
    int table_size = hash_table->table_size;
    int hash = String_Hasher(key) % table_size; 

    Hash_closed_node_t *node = hash_table->table[hash];
    Hash_closed_node_t *prev = NULL;

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0) 
        {
            if (prev == NULL)  
                hash_table->table[hash] = node->next; 
            else  
                prev->next = node->next;  
            free_closed_hash_node(node); 
            hash_table->keysCount--;  
            return OK;
        }
        prev = node;
        node = node->next;
    }

    return ERROR_NO_ELEM; 
}


void print_closed_hash_table(Hash_closed_table_t *hash_table)
{
    printf("Размер таблицы: %d \n", hash_table->table_size);
    printf("Количество занятых ячеек: %d \n", hash_table->keysCount);

    for (int i = 0; i < hash_table->table_size; i++)
    {
        Hash_closed_node_t *node = hash_table->table[i];
        if (node != NULL) 
        {
            printf("Индекс %d: ", i);
            while (node != NULL)  
            {
                printf("%s -> ", node->key);
                node = node->next;
            }
            printf("NULL\n");
        }
    }
}

int init_closed_table_from_file(Hash_closed_table_t **hash_table, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return ERROR_FILE;

    Hash_closed_table_t *new_table = malloc(sizeof(Hash_closed_table_t));
    if (new_table == NULL) 
    {
        fclose(file);
        return ERROR_MEMORY; 
    }
    init_closed_hash_table(new_table, base_size_cl);  
    free_closed_table(*hash_table);  

    *hash_table = new_table;

    char word[MAX_STR_LEN];

    while (fscanf(file, "%s", word) != EOF) 
    {
        int rc = add_elem_to_closed_table(hash_table, word);  
        if ((rc != OK) && (rc != ERROR_ALREADY_EXISTS))
        {
            free_closed_table(new_table);
            fclose(file);
            return rc;
        }
    }
    fclose(file);
    return OK;
}

Hash_closed_node_t *find_closed_node(Hash_closed_table_t *hash_table, char *key, int *cmp_cnt)
{
    int table_size = hash_table->table_size;
    int hash = String_Hasher(key) % table_size;

    Hash_closed_node_t *node = hash_table->table[hash];
    while (node != NULL)
    {
        (*cmp_cnt)++;
        if (strcmp(node->key, key) == 0)  
            return node;
        node = node->next;  
    }
    return NULL; 
}


void closed_hash_delete_words_starting_with(Hash_closed_table_t *hash_table, char letter, int *cmp_cnt) 
{
    for (int i = 0; i < hash_table->table_size; i++)
    {
        Hash_closed_node_t *node = hash_table->table[i];
        Hash_closed_node_t *prev = NULL;

        while (node != NULL)
        {
            (*cmp_cnt)++;
            if (node->key[0] == letter) 
            {
                if (prev == NULL) 
                    hash_table->table[i] = node->next; 
                else
                    prev->next = node->next; 
                free_closed_hash_node(node); 
                hash_table->keysCount--;  
                break;;
            }
            prev = node;
            node = node->next; 
        }
    }
}

