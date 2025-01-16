#include "tree.h"

struct tree_node_t *create_node(const char *name)
{
    struct tree_node_t *node = malloc(sizeof(struct tree_node_t));
    if (node)
    {
        node->name = strdup(name);
        if (!node->name)
        {
            free(node);
            return NULL;
        }
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
    }
    return node;
}

void node_free(struct tree_node_t *node)
{
    if (node)
    {
        free(node->name);
        free(node);
    }
}

void tree_free(struct tree_node_t *tree)
{
    if (tree == NULL)
        return;

    tree_free(tree->left);
    tree_free(tree->right);
    node_free(tree);
}

int height(struct tree_node_t *node)
{
    return node ? node->height : 1;
}

int get_balance(struct tree_node_t *node)
{
    return node ? height(node->left) - height(node->right) : 1;
}

struct tree_node_t *insert_node(struct tree_node_t *tree, struct tree_node_t *node)
{
    if (tree == NULL)
        return node;
    int cmp = strcmp(node->name, tree->name);
    if (cmp == 0)
        return tree;
    else if (cmp < 0)
        tree->left = insert_node(tree->left, node);
    else
        tree->right = insert_node(tree->right, node);
    tree->height = 1 + max(height(tree->left), height(tree->right));
    return tree;
}

void delete_words_starting_with(struct tree_node_t **root, char letter)
{
    if (*root == NULL)
        return;

    if ((*root)->name[0] == letter)
    {
        *root = delete_node(*root, (*root)->name, 0);
        delete_words_starting_with(root, letter);
    }
    else
    {
        if ((*root)->name[0] > letter)
            delete_words_starting_with(&((*root)->left), letter);
        else
            delete_words_starting_with(&((*root)->right), letter);
    }
}

void get_cmp_cnt(struct tree_node_t **root, char letter, int *cmp_cnt)
{
    if (*root == NULL)
        return;

    if ((*root)->name[0] == letter)
    {
        (*cmp_cnt)++;
        *root = delete_node(*root, (*root)->name, 1);
    }
    else
    {
        (*cmp_cnt)++;
        if ((*root)->name[0] > letter)
            get_cmp_cnt(&((*root)->left), letter, cmp_cnt);
        else
            get_cmp_cnt(&((*root)->right), letter, cmp_cnt);
    }
}

void in_order(struct tree_node_t *node)
{
    if (node != NULL)
    {
        in_order(node->left);
        printf("%s %d\n", node->name, node->height);
        in_order(node->right);
    }
}

void read_words_from_file(const char *filename, struct tree_node_t **root)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return;
    char word[MAX_STR_LEN];
    while (fscanf(file, "%s", word) != EOF)
    {
        struct tree_node_t *new_node = create_node(word);
        *root = insert_node(*root, new_node);
    }
    fclose(file);
}

struct tree_node_t *find_elem(struct tree_node_t *tree, const char *name, int *cmp_cnt)
{
    int cmp;
    while (tree != NULL)
    {
        cmp = strcmp(name, tree->name);
        (*cmp_cnt)++;
        if (cmp == 0)
            return tree;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return NULL;
}

struct tree_node_t *find_min(struct tree_node_t *node)
{
    while (node->left != NULL)
        node = node->left;

    return node;
}

struct tree_node_t *delete_node(struct tree_node_t *tree, const char *name, int balance)
{
    if (tree == NULL)
        return tree;
    int cmp = strcmp(name, tree->name);
    if (cmp < 0)
        tree->left = delete_node(tree->left, name, balance);
    else if (cmp > 0)
        tree->right = delete_node(tree->right, name, balance);
    else
    {
        if (tree->left == NULL)
        {
            struct tree_node_t *temp = tree->right;
            node_free(tree);
            if (balance == 0)
            {
                int balance_cnt = 0;
                int prev_cnt = 0;
                tree = balance_tree(tree, &balance_cnt);
                while (balance_cnt != prev_cnt)
                {
                    prev_cnt = balance_cnt;
                    tree = balance_tree(tree, &balance_cnt);
                }
            }
            return temp;
        }
        else if (tree->right == NULL)
        {
            struct tree_node_t *temp = tree->left;
            if (balance == 0)
            {
                int balance_cnt = 0;
                int prev_cnt = 0;
                tree = balance_tree(tree, &balance_cnt);
                while (balance_cnt != prev_cnt)
                {
                    prev_cnt = balance_cnt;
                    tree = balance_tree(tree, &balance_cnt);
                }
            }
            node_free(tree);
            return temp;
        }

        struct tree_node_t *temp = find_min(tree->right);
        free(tree->name);
        tree->name = strdup(temp->name);
        tree->right = delete_node(tree->right, temp->name, balance);
    }
    tree->height = 1 + max(height(tree->left), height(tree->right));

    if (balance == 0)
    {
    int balance_cnt = 0;
    int prev_cnt = 0;
    tree = balance_tree(tree, &balance_cnt);
    while (balance_cnt != prev_cnt)
    {
        prev_cnt = balance_cnt;
        tree = balance_tree(tree, &balance_cnt);
    }
    }
    return tree;
}

struct tree_node_t *right_rotate(struct tree_node_t *root)
{
    struct tree_node_t *first = root->left;
    struct tree_node_t *second = first->right;

    first->right = root;
    root->left = second;

    root->height = 1 + max(height(root->left), height(root->right));
    first->height = 1 + max(height(first->left), height(first->right));

    return first;
}

struct tree_node_t *left_rotate(struct tree_node_t *root)
{
    struct tree_node_t *first = root->right;
    struct tree_node_t *second = first->left;

    first->left = root;
    root->right = second;

    root->height = 1 + max(height(root->left), height(root->right));
    first->height = 1 + max(height(first->left), height(first->right));

    return first;
}

struct tree_node_t *balance_node(struct tree_node_t *node, int *balance_cnt)
{
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && get_balance(node->left) >= 0)
    {
        (*balance_cnt)++;
        return right_rotate(node);
    }

    if (balance < -1 && get_balance(node->right) <= 0)
    {
        (*balance_cnt)++;
        return left_rotate(node);
    }

    if (balance > 1 && get_balance(node->left) < 0)
    {
        (*balance_cnt)++;
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && get_balance(node->right) > 0)
    {
        (*balance_cnt)++;
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

struct tree_node_t *balance_tree(struct tree_node_t *tree, int *balance_cnt)
{
    if (tree == NULL)
        return NULL;

    tree->left = balance_tree(tree->left, balance_cnt);
    tree->right = balance_tree(tree->right, balance_cnt);

    return balance_node(tree, balance_cnt);
}

static void tree_print_dot_null(FILE *f, const char *name, int nullcount)
{
    fprintf(f, "  null%d [shape=point];\n", nullcount);

    fprintf(f, "  %s -> null%d;\n", name, nullcount);
}

static void tree_print_dot_aux(FILE *f, struct tree_node_t *node)
{
    static int nullcount = 0;

    if (node->left)
    {
        fprintf(f, "  %s -> %s;\n", node->name, node->left->name);
        tree_print_dot_aux(f, node->left);
    }
    else
        tree_print_dot_null(f, node->name, nullcount++);

    if (node->right)
    {
        fprintf(f, "  %s -> %s;\n", node->name, node->right->name);
        tree_print_dot_aux(f, node->right);
    }
    else
        tree_print_dot_null(f, node->name, nullcount++);
}

void tree_export_to_dot(FILE *f, const char *tree_name, struct tree_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);
    fprintf(f, "  node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(f, "\n");
    else if (!tree->right && !tree->left)
        fprintf(f, "  %s;\n", tree->name);
    else
        tree_print_dot_aux(f, tree);

    fprintf(f, "}\n");
}
