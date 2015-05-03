#include <stdlib.h>

#include "binary_tree.h"

binary_tree_node *
binary_tree_search(binary_tree *tree, int value)
{
    binary_tree_node *node = tree;

    while (node && node->value != value)
    {
        if (node->value < value)
            node = node->right;
        else if (node->value > value)
            node = node->left;
    }
    
    return node;
}

static binary_tree_node *
binary_tree_create_node(int value)
{
    binary_tree_node *node = malloc(sizeof(binary_tree_node));
    if (node != NULL)
    {
        node->left = NULL;
        node->right = NULL;
        node->value = value;
    }

    return node;
}

binary_tree *
binary_tree_insert(binary_tree *tree, int value)
{
    binary_tree_node *node = tree;
    binary_tree_node *prev = node;

    if (node == NULL)
        return binary_tree_create_node(value);

    while (node != NULL)
    {
        if (node->value == value)
            return tree;

        prev = node;
        if (node->value < value)
            node = node->right;
        else if (node->value > value)
            node = node->left;
    }

    node = binary_tree_create_node(value);
    if (node == NULL)
        return tree;

    if (prev->value < value)
        prev->right = node;
    else if (prev->value > value)
        prev->left = node;

    return tree;
}

binary_tree *
binary_tree_remove(binary_tree *tree, int value)
{
    binary_tree_node *node = tree;
    binary_tree_node *prev = NULL;

    while (node && node->value != value)
    {
        prev = node;
        if (node->value < value)
            node = node->right;
        else if (node->value > value)
            node = node->left;
    }

    if (node == NULL)
        return tree;

    if (node->left == NULL && node->right == NULL)
    {
        if (prev == NULL)
            tree = NULL;
        else if (prev->value < value)
            prev->right = NULL;
        else if (prev->value > value)
            prev->left = NULL;

        free(node);
    }
    else if (node->left == NULL || node->right == NULL)
    {
        binary_tree_node *child;

        child = node->left;
        if (child == NULL)
            child = node->right;

        if (prev == NULL)
            tree = child;
        else if (prev->value < value)
            prev->right = child;
        else if (prev->value > value)
            prev->left = child;

        free(node);
    }
    else
    {
        binary_tree_node *smallest = node->right;
        while (smallest->left != NULL)
            smallest = smallest->left;

        node->value = smallest->value;

        node->right = binary_tree_remove(node->right, node->value);
    }

    return tree;
}
