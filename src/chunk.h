#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT, // Load an 8-bit constant
    OP_CONSTANT_LONG, // Load a 24-bit constant
    OP_RETURN, // Return from the current function
} OpCode;

typedef struct {
    int offset;
    int number;
} LineStart;

typedef struct {
    int count;
    int capacity;
    uint8_t *code;

    int lines_count;
    int lines_capacity;
    LineStart *lines;

    ValueArray constants;
} Chunk;

void init_chunk(Chunk *chunk);
void free_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte, int line);
void write_constant_to_chunk(Chunk *chunk, Value value, int line);
int add_constant_to_chunk(Chunk *chunk, Value value);
int instruction_line_from_chunk(Chunk *chunk, int instruction);

#endif