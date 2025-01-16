#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 200
#define OK 0

#define max(x, y) ( (x) > (y) ? (x) : (y) )

struct tree_node_t
{
    char *name;
    int height;
    struct tree_node_t *left;
    struct tree_node_t *right;
};

struct tree_node_t *create_node(const char *name);

void in_order(struct tree_node_t *node);

void read_words_from_file(const char *filename, struct tree_node_t **root);

void delete_words_starting_with(struct tree_node_t **root, char letter);

void get_cmp_cnt(struct tree_node_t **root, char letter, int *cmp_cnt);

void tree_free(struct tree_node_t *tree);

void tree_export_to_dot(FILE *f, const char *tree_name, struct tree_node_t *tree);

struct tree_node_t *find_elem(struct tree_node_t *tree, const char *name,  int *cmp_cnt);

struct tree_node_t *insert_node(struct tree_node_t *tree, struct tree_node_t *node);

struct tree_node_t *delete_node(struct tree_node_t *tree, const char *name, int balance);

struct tree_node_t *balance_tree(struct tree_node_t *tree, int* balance_cnt);

#endif
