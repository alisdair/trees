#pragma once

typedef struct binary_tree_node
{
    struct binary_tree_node *left;
    struct binary_tree_node *right;
    int value;
} binary_tree_node;

typedef struct binary_tree_node binary_tree;

binary_tree_node *
binary_tree_search(binary_tree *tree, int value);

binary_tree *
binary_tree_insert(binary_tree *tree, int value);

binary_tree *
binary_tree_remove(binary_tree *tree, int value);
