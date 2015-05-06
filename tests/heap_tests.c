#include "test.h"
#include "heap.h"

DEFINE_TEST(test_everything)
{
    heap_t *heap = heap_with_capacity(4);

    test_assert(heap_length(heap) == 0, "heap [] has length 0");

    heap = heap_push(heap, 5);
    test_assert(heap_peek(heap) == 5, "top of heap [5] is 5");

    heap = heap_push(heap, 3);
    test_assert(heap_peek(heap) == 3, "top of heap [5, 3] is 3");

    heap = heap_push(heap, 7);
    test_assert(heap_peek(heap) == 3, "top of heap [5, 3, 7] is 3");

    heap = heap_push(heap, 1);
    heap = heap_push(heap, -5);
    heap = heap_push(heap, 1);
    heap = heap_push(heap, 10);

    test_assert(heap_peek(heap) == -5, "top of heap [5, 3, 7, 1, -5, 1, 10] is -5");
    test_assert(heap_length(heap) == 7, "heap [5, 3, 7, 1, -5, 1, 10] has length 7");

    test_assert(heap_pop(heap) == -5, "popping heap [5, 3, 7, 1, -5, 1, 10] gives -5");
    test_assert(heap_pop(heap) == 1, "popping heap [5, 3, 7, 1, 1, 10] gives 1");
    test_assert(heap_pop(heap) == 1, "popping heap [5, 3, 7, 1, 10] gives 1");

    test_assert(heap_pop(heap) == 3, "popping heap [5, 3, 7, 10] gives 3");
    test_assert(heap_pop(heap) == 5, "popping heap [5, 7, 10] gives 5");
    test_assert(heap_pop(heap) == 7, "popping heap [7, 10] gives 7");
    test_assert(heap_pop(heap) == 10, "popping heap [10] gives 10");

    test_assert(heap_length(heap) == 0, "heap [] has length 0");

    return NULL;
}

DEFINE_TEST(all_tests)
{
    test_run(test_everything);

    return NULL;
}

TEST_SUITE(all_tests);
