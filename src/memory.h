#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, count_old, count_new) \
    (type *)reallocate(pointer, sizeof(type) * (count_old), \
        sizeof(type) * (count_new))

#define FREE_ARRAY(type, pointer, count_old) \
    reallocate(pointer, sizeof(type) * (count_old), 0)

void *reallocate(void *pointer, size_t size_old, size_t size_new);

#endif