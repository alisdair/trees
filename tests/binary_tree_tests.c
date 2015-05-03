#include "test.h"
#include "binary_tree.h"

DEFINE_TEST(test_insert_empty)
{
    return NULL;
}

DEFINE_TEST(test_remove_empty)
{
    return NULL;
}

DEFINE_TEST(all_tests)
{
    test_run(test_insert_empty);
    test_run(test_remove_empty);

    return NULL;
}

TEST_SUITE(all_tests);
