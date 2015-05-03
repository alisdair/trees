#include "test.h"
#include "binary_tree.h"

DEFINE_TEST(test_insert_empty)
{
    binary_tree *tree = NULL;
    tree = binary_tree_insert(tree, 5);

    test_assert(tree != NULL, "insert(NULL, x) returns new tree");
    test_assert(tree->value == 5, "value is stored in tree");
    test_assert(tree->left == NULL, "tree has no left child");
    test_assert(tree->right == NULL, "tree has no right child");

    return NULL;
}

DEFINE_TEST(test_insert_2_1_3)
{
    binary_tree *tree = NULL;

    tree = binary_tree_insert(tree, 2);
    tree = binary_tree_insert(tree, 3);
    tree = binary_tree_insert(tree, 1);

    test_assert(tree != NULL, "results in a tree");
    test_assert(tree->value == 2, "first value is in root node");

    test_assert(tree->left != NULL, "left child is a tree");
    test_assert(tree->left->value == 1, "left child value is 1");
    test_assert(tree->left->left == NULL, "left child has no left child");
    test_assert(tree->left->right == NULL, "left child has no right child");

    test_assert(tree->right != NULL, "right child is a tree");
    test_assert(tree->right->value == 3, "right child value is 3");
    test_assert(tree->right->left == NULL, "right child has no left child");
    test_assert(tree->right->right == NULL, "right child has no right child");

    return NULL;
}

DEFINE_TEST(test_search_empty)
{
    binary_tree *tree = NULL;
    binary_tree_node *node = binary_tree_search(tree, 0);
    test_assert(node == NULL, "search for 0 finds nothing");

    return NULL;
}

DEFINE_TEST(test_search_2_1_3)
{
    binary_tree *tree = NULL;
    binary_tree_node *node;

    tree = binary_tree_insert(tree, 2);
    tree = binary_tree_insert(tree, 3);
    tree = binary_tree_insert(tree, 1);

    node = binary_tree_search(tree, 2);
    test_assert(node == tree, "search for 2 finds root node");

    node = binary_tree_search(tree, 3);
    test_assert(node == tree->right, "search for 3 finds right child");

    node = binary_tree_search(tree, 1);
    test_assert(node == tree->left, "search for 1 finds left child");

    node = binary_tree_search(tree, 0);
    test_assert(node == NULL, "search for 0 finds nothing");

    return NULL;
}

DEFINE_TEST(test_remove_empty)
{
    binary_tree *tree = NULL;

    tree = binary_tree_remove(tree, 2);
    test_assert(tree == NULL, "remove on empty tree returns NULL");

    return NULL;
}

DEFINE_TEST(all_tests)
{
    test_run(test_insert_empty);
    test_run(test_insert_2_1_3);

    test_run(test_search_empty);
    test_run(test_search_2_1_3);

    test_run(test_remove_empty);

    return NULL;
}

TEST_SUITE(all_tests);
