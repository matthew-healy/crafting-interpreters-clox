#include <stdlib.h>

#include "memory.h"

void *reallocate(void *pointer, size_t size_old, size_t size_new) {
    if (size_new == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, size_new);
    if (result == NULL) exit(1);
    return result;
}