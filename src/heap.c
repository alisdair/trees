#include <stdlib.h>
#include <stdint.h>

#include "heap.h"

#define DEFAULT_HEAP_CAPACITY 256
#define MAXIMUM_HEAP_SIZE (SIZE_MAX / sizeof(int))

heap_t *
heap_new()
{
    return heap_with_capacity(DEFAULT_HEAP_CAPACITY);
}

heap_t *
heap_with_capacity(size_t capacity)
{
    if (capacity > MAXIMUM_HEAP_SIZE)
        exit(1);

    heap_t *heap = malloc(sizeof(heap_t));
    if (heap == NULL)
        exit(1);

    heap->len = 0;
    heap->capacity = capacity;
    heap->vec = malloc(capacity * sizeof(int));

    return heap;
}

size_t
heap_length(heap_t *heap)
{
    return heap->len;
}

void
heap_resize(heap_t *heap, size_t capacity)
{
    if (capacity > MAXIMUM_HEAP_SIZE)
        exit(1);

    heap->vec = realloc(heap->vec, capacity * sizeof(int));
    if (heap->vec == NULL)
        exit(1);

    heap->capacity = capacity;
}

int
heap_peek(heap_t *heap)
{
    // FIXME this ain't Erlang, buddy
    if (heap->len == 0)
        exit(1);

    return heap->vec[0];
}

static inline void
heap_swap(heap_t *heap, size_t a, size_t b)
{
    int item = heap->vec[a];
    heap->vec[a] = heap->vec[b];
    heap->vec[b] = item;
}

static void
heap_sift_down(heap_t *heap, size_t parent)
{
    // Sift the item at index down through the heap until valid

    // Compare item at index with left child and right child. If item
    // is smallest, then we are finished, return. Otherwise, swap item
    // with the smallest, then call heap_sift_down with the index of the
    // swapped item.

    // Several situations are possible:
    //
    // 1. Item at index has no children, in which case we are done. Note
    //    that if an item has no left child, it can have no right child,
    //    as a binary heap is a complete tree.
    // 2. Item has left child only, in which case we can swap if needed
    //    and then we are done.
    // 3. Item has left and right child, and one is smaller than parent,
    //    in which case we can swap with the smallest, then recurse.
    // 4. Item has left and right child, but parent is smallest, and we
    //    are done.
    //
    // When calculating the left and right indices, it's possible for
    // the variables to overflow (if the heap length is close to
    // SIZE_MAX). In case this happens, we need to check not only that
    // the indices are less than the heap length, but also that they
    // are greater than the parent index.

    size_t left, right;

    // Note: both of these can overflow, but size_t is unsigned so this
    // is defined behaviour and we check for it later.
    left = 2 * parent + 1;
    right = 2 * parent + 2;

    // Left child is past the end of the heap, either because it's greater
    // than the last heap item, or because it has overflowed size_t and is
    // therefore now smaller than the parent index
    if (left >= heap->len || left < parent)
        return;

    // Same as above but for the right child
    if (right >= heap->len || right < parent)
    {
        if (heap->vec[left] < heap->vec[parent])
            heap_swap(heap, left, parent);

        return;
    }

    // If we got here, we know that both children exist. First check if
    // the left child is smaller than the parent and no larger than the
    // right child; if so, swap and recurse on the left tree.
    if (heap->vec[left] < heap->vec[parent] &&
            heap->vec[left] <= heap->vec[right])
    {
        heap_swap(heap, left, parent);
    }

    // Otherwise, if the right child is smaller than the parent then we
    // already know that it must be smaller than the left child, so
    // swap and recurse on the right tree.
    else if (heap->vec[right] < heap->vec[parent])
    {
        heap_swap(heap, right, parent);
        heap_sift_down(heap, right);
    }

    // If we fall through to this point, then we know that the parent is
    // the smallest of the three nodes, which means we're done, so stop.
}

int
heap_pop(heap_t *heap)
{
    int item;

    if (heap->len == 0)
        exit(1);

    item = heap->vec[0];

    heap->vec[0] = heap->vec[heap->len - 1];
    heap->len--;
    heap_sift_down(heap, 0);

    return item;
}

static void
heap_grow(heap_t *heap)
{
    size_t capacity;

    if (heap->capacity > MAXIMUM_HEAP_SIZE / 2)
        capacity = MAXIMUM_HEAP_SIZE;
    else
        capacity = heap->capacity * 2;

    heap_resize(heap, capacity);
}

static void
heap_sift_up(heap_t *heap, size_t index)
{
    // Sift the item at index up through the heap until valid

    // Compare item at index with parent. If item is larger, then we are
    // finished, return. Otherwise, swap item with the parent, then call
    // heap_sift_up with the index of the parent.
    //
    // Note that we do not need to be concerned about the other child of
    // this item's parent. If item < parent and the heap is otherwise
    // valid, then parent < other and so item < other. Swapping item
    // with parent will therefore leave the other sub-tree valid also;
    // our only concern is that the item might also be smaller than its
    // grandparent, and so on.

    size_t parent;

    if (index == 0)
        return;

    parent = (index - 1) / 2;

    if (heap->vec[index] >= heap->vec[parent])
        return;

    heap_swap(heap, index, parent);

    if (parent != 0)
        heap_sift_up(heap, parent);
}

heap_t *
heap_push(heap_t *heap, int item)
{
    if (heap->len == heap->capacity)
        heap_grow(heap);

    heap->vec[heap->len] = item;
    heap->len++;

    heap_sift_up(heap, heap->len - 1);

    return heap;
}
