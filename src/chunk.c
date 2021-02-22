#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void init_chunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;

    chunk->lines_count = 0;
    chunk->lines_capacity = 0;
    chunk->lines = NULL;

    init_value_array(&chunk->constants);
}

void free_chunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(LineStart, chunk->lines, chunk->lines_capacity);
    free_value_array(&chunk->constants);
    init_chunk(chunk);
}

void write_chunk(Chunk *chunk, uint8_t byte, int line) {
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

    if (
        // it's not the first line we're recording
        chunk->lines_count > 0 &&
        // and we already have this line recorded
        chunk->lines[chunk->lines_count - 1].number == line
    ) {
        return;
    }

    if (chunk->lines_capacity < chunk->lines_count + 1) {
        int capacity_old = chunk->lines_capacity;
        chunk->lines_capacity = GROW_CAPACITY(capacity_old);
        chunk->lines = GROW_ARRAY(
            LineStart, chunk->lines,
            capacity_old, chunk->lines_capacity
        );
    }

    LineStart *new_line = &chunk->lines[chunk->lines_count++];
    new_line->offset = chunk->count - 1;
    new_line->number = line;
}

int add_constant_to_chunk(Chunk *chunk, Value value) {
    write_value_array(&chunk->constants, value);
    return chunk->constants.count - 1;
}

int instruction_line_from_chunk(Chunk *chunk, int instruction) {
    int start = 0;
    int end = chunk->lines_count - 1;

    for (;;) {
        int mid = (start + end) / 2;
        LineStart *line = &chunk->lines[mid];
        if (instruction < line->offset) {
            end = mid - 1;
        } else if (
            mid == chunk->lines_count - 1 ||
            instruction < chunk->lines[mid + 1].offset
        ) {
            return line->number;
        } else {
            start = mid + 1;
        }
    }
}