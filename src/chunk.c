#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void init_chunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
}

void free_chunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    init_chunk(chunk);
}

void write_chunk(Chunk *chunk, uint8_t byte) {
    if (chunk->capacity < chunk->count + 1) {
        int capacity_old = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(capacity_old);
        chunk->code = GROW_ARRAY(
            uint8_t, chunk->code, 
            capacity_old, chunk->capacity
        );
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}