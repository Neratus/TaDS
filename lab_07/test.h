#ifndef TEST_TREE_H
#define TEST_TREE_H

#include "tree.h"
#include "hash.h"
#include "hash_closed.h"
#include <math.h>

#define ERROR_STR_INPUT -4
#define ERROR_STR_SIZE -5

void test(void);

int read_line(char *str, size_t str_max, FILE *f);

void post_order(struct tree_node_t *node) ;

#endif
