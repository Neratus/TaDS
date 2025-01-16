#include "hash.h"

double rehash_size = 0.75;
int base_size = 31;
double allocate_incr = 1.2;

// 0 = empty
// 1 = deleted
//  2 = key


static int String_Hasher_first(char *key)
{
    int hash_value = 0;
    size_t length = strlen(key);
    
    for (size_t i = 0; i < length; i++)
        hash_value = (hash_value * 2 + key[i]);
    return hash_value;
}

static int String_Hasher_second(char *key)
{
    int length = strlen(key);
    return length;
}

int find_next_simple(int cur)
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

static Hash_node_t *create_hash_node(char *name)
{
    Hash_node_t *node = malloc(sizeof(Hash_node_t));
    if (node)
    {
        node->key = strdup(name);
        if (!node->key) 
        {
            free(node); 
            return NULL;
        }
        node->hash_1 = String_Hasher_first(name);
        node->hash_2 = String_Hasher_second(name);
        node->cell_state = 2;
    }
    return node;
}

static void free_hash_node(Hash_node_t *node)
{
    if (node)
    {
        free(node->key);
        free(node);
    }
}

void init_hash_table(Hash_table_t *hash_table, int size) 
{
    hash_table->table = malloc(size * sizeof(Hash_node_t));
    for (int i = 0; i < size; i++) 
    {
        hash_table->table[i] = malloc(sizeof(Hash_node_t));
        hash_table->table[i]->key = NULL;
        hash_table->table[i]->hash_1 = 0;
        hash_table->table[i]->hash_2 = 0;
        hash_table->table[i]->cell_state = 0; 
    }
    hash_table->deleted_cnt = 0;
    hash_table->keysCount = 0;
    hash_table->table_size = size;
}

void free_table(Hash_table_t *hash_table)
{
    if (hash_table) 
    {
        if (hash_table->table)
        {
            for (int i = 0; i < hash_table->table_size; i++) 
            {
                if (hash_table->table[i]->cell_state != 0)
                    free_hash_node(hash_table->table[i]);
            }
            free(hash_table->table);
            hash_table->table = NULL;
        }
        free(hash_table); 
    }
}

static void rehash_hash_table(Hash_table_t **hash_table_ptr, int new_table_size) 
{
    Hash_table_t *old_table = *hash_table_ptr; 

    Hash_table_t *new_table = malloc(sizeof(Hash_table_t));
    init_hash_table(new_table, new_table_size);
    for (int i = 0; i < old_table->table_size; i++) 
    {
        if (old_table->table[i]->cell_state == 2) 
        {
            Hash_node_t *node = old_table->table[i]; 
            int pos = node->hash_1 % new_table_size;
            int hash_2 = node->hash_2 % new_table_size;

            while (new_table->table[pos]->cell_state != 0) 
                pos = (pos + hash_2) % new_table_size; 

            new_table->table[pos] = node; 
            new_table->table[pos]->cell_state = 2; 
            new_table->keysCount++;
        }
    }
    *hash_table_ptr = new_table;
}

int add_elem_to_table(Hash_table_t **hash_table_ptr, char *key)
{
    if ((*hash_table_ptr)->keysCount >= rehash_size * (*hash_table_ptr)->table_size) 
	{
		if ((*hash_table_ptr)->deleted_cnt > (1-rehash_size) * (*hash_table_ptr)->table_size)
		    rehash_hash_table(hash_table_ptr, (*hash_table_ptr)->table_size);
		else 
		    rehash_hash_table(hash_table_ptr, find_next_simple((int)(allocate_incr *(*hash_table_ptr)->table_size)));
    }
    int table_size = (*hash_table_ptr)->table_size;
    int hasher_1 = String_Hasher_first(key);
	int hasher_2 = String_Hasher_second(key);

    int cur_hash_1 = hasher_1 % table_size;
	int cur_hash_2 = hasher_2 % table_size;

    int index = cur_hash_1;
	int first_deleted = -1;


    while ((*hash_table_ptr)->table[index]->cell_state != 0)
	{
	    if ((strcmp((*hash_table_ptr)->table[index]->key,key) == 0) && ((*hash_table_ptr)->table[index]->cell_state == 2))
	        return ERROR_ALREADY_EXISTS;
        
	    if (((*hash_table_ptr)->table[index]->cell_state == 1) && (first_deleted == -1))
	        first_deleted = index;

	    index = (index + cur_hash_2) % table_size;
	}
    Hash_node_t *node = create_hash_node(key);
    if (!node)
        return ERROR_MEMORY;
    if (first_deleted == -1)
	{
	    (*hash_table_ptr)->table[index] = node;
	    (*hash_table_ptr)->keysCount++;
	}
	else
	{
        (*hash_table_ptr)->table[first_deleted] = node;
	    (*hash_table_ptr)->deleted_cnt--;
	}
	return OK;
}

int delete_elem_from_table(Hash_table_t *hash_table, char *key)
{
    int table_size = hash_table->table_size;
    int hash_1 = String_Hasher_first(key) % table_size;
	int hash_2 = String_Hasher_second(key) % table_size;
	    
    int index = hash_1;
	while (hash_table->table[index]->cell_state != 0)
	{
	    if ((hash_table->table[index]->cell_state == 2) && (strcmp(hash_table->table[index]->key, key) == 0))
        {
            hash_table->table[index]->cell_state = 1;
            hash_table->deleted_cnt++;
	        return OK;
        }

	    index = (index + hash_2) % table_size;
	}
    
	return ERROR_NO_ELEM;
}

void print_hash_table(Hash_table_t *hash_table)
{
    printf("Размер таблицы: %d \n", hash_table->table_size);
    printf("Количество занятых ячеек: %d \n", hash_table->keysCount);
    printf("Количество удаленных значений: %d \n", hash_table->deleted_cnt);
    for (int i = 0; i < hash_table->table_size; i++)
    {
        if (hash_table->table[i]->cell_state != 0) 
        {
            printf("Инекс ячейки: %d ",i);
            printf("Значение хэш функции: %d ",hash_table->table[i]->hash_1 % hash_table->table_size);
            printf("Статус ячейки :");
            if (hash_table->table[i]->cell_state == 1)
                printf("Удалено ");
            else 
                printf("Занято ключом ");
            printf("Значение :%s \n",hash_table->table[i]->key);
        }
    }
}

int init_table_from_file(Hash_table_t **hash_table, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return ERROR_FILE;

    Hash_table_t *new_table = malloc(sizeof(Hash_table_t));
    if (new_table == NULL) 
    {
        fclose(file);
        return ERROR_MEMORY; 
    }
    init_hash_table(new_table, base_size); 

    free_table(*hash_table);

    *hash_table = new_table;

    char word[MAX_STR_LEN];

    while (fscanf(file, "%s", word) != EOF) 
    {
        int rc = add_elem_to_table(hash_table, word);
        if ((rc != OK) && (rc != ERROR_ALREADY_EXISTS))
        {
            free_table(new_table);
            fclose(file);
            return rc;
        }
    }
    fclose(file);
    return OK;
}

Hash_node_t *find_node(Hash_table_t *hash_table, char *key, int *cmp_cnt)
{
    int table_size = hash_table->table_size;
    int hash_1 = String_Hasher_first(key) % table_size;
	int hash_2 = String_Hasher_second(key) % table_size;
	    
    int index = hash_1;
	while (hash_table->table[index]->cell_state != 0)
	{
        (*cmp_cnt)++;
	    if ((hash_table->table[index]->cell_state == 2) && (strcmp(hash_table->table[index]->key, key) == 0))
	        return hash_table->table[index];

	    index = (index + hash_2) % table_size;
	}
	return NULL;
}

void hash_delete_words_starting_with(Hash_table_t *hash_table, char letter, int *cmp_cnt) 
{
    for (int i = 0; i < hash_table->table_size; i++)
    {
        (*cmp_cnt)++;
        if (hash_table->table[i]->cell_state == 2) 
        {
            if (hash_table->table[i]->key[0] == letter) 
            {
                free(hash_table->table[i]->key); 
                hash_table->table[i]->cell_state = 1; 
                hash_table->keysCount--;
                hash_table->deleted_cnt++;
            }
        }
    }
}
