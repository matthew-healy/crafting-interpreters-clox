#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT, // Load a constant
    OP_NIL,      // Load nil
    OP_TRUE,     // Load true
    OP_FALSE,    // Load false
    OP_ADD,      // Add two numeric values
    OP_SUBTRACT, // Subtract one numeric value from another
    OP_MULTIPLY, // Multiply two numeric values
    OP_DIVIDE,   // Divide one numeric value by another
    OP_NOT,      // Negate a boolean value
    OP_NEGATE,   // Negate a numeric value
    OP_RETURN,   // Return from the current function
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    int *lines;
    ValueArray constants;
} Chunk;

void init_chunk(Chunk *chunk);
void free_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte, int line);
int add_constant_to_chunk(Chunk *chunk, Value value);

#endif