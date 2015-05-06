#pragma once
#include <stddef.h>

typedef struct
{
    int *vec;
    size_t capacity;
    size_t len;
} heap_t;

heap_t *
heap_new();

heap_t *
heap_with_capacity(size_t capacity);

size_t
heap_length(heap_t *heap);

void
heap_resize(heap_t *heap, size_t capacity);

int
heap_peek(heap_t *heap);

int
heap_pop(heap_t *heap);

heap_t *
heap_push(heap_t *heap, int item);
