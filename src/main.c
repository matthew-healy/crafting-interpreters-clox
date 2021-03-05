#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
    init_vm();
    Chunk chunk;
    init_chunk(&chunk);

    // -((1.2 + 3.4) / 5.6)
    // int constant = addConstant(&chunk, 1.2);
    // writeChunk(&chunk, OP_CONSTANT, 123);
    // writeChunk(&chunk, constant, 123);

    // constant = addConstant(&chunk, 3.4);
    // writeChunk(&chunk, OP_CONSTANT, 123);
    // writeChunk(&chunk, constant, 123);

    // writeChunk(&chunk, OP_ADD, 123);

    // constant = addConstant(&chunk, 5.6);
    // writeChunk(&chunk, OP_CONSTANT, 123);
    // writeChunk(&chunk, constant, 123);

    // writeChunk(&chunk, OP_DIVIDE, 123);

    // writeChunk(&chunk, OP_NEGATE, 123);

    // writeChunk(&chunk, OP_RETURN, 123);


    // 1 * 2 + 3
    // int constant = add_constant_to_chunk(&chunk, 1);
    // write_chunk(&chunk, OP_CONSTANT, 1);
    // write_chunk(&chunk, constant, 1);

    // constant = add_constant_to_chunk(&chunk, 2);
    // write_chunk(&chunk, OP_CONSTANT, 1);
    // write_chunk(&chunk, constant, 1);

    // write_chunk(&chunk, OP_MULTIPLY, 1);

    // constant = add_constant_to_chunk(&chunk, 3);
    // write_chunk(&chunk, OP_CONSTANT, 1);
    // write_chunk(&chunk, constant, 1);

    // write_chunk(&chunk, OP_ADD, 1);

    // write_chunk(&chunk, OP_RETURN, 1);

    // 1 + 2 * 3
    // int constant = add_constant_to_chunk(&chunk, 1);
    // write_chunk(&chunk, OP_CONSTANT, 1);
    // write_chunk(&chunk, constant, 1);

    // constant = add_constant_to_chunk(&chunk, 2);
    // write_chunk(&chunk, OP_CONSTANT, 1);
    // write_chunk(&chunk, constant, 1);

    // constant = add_constant_to_chunk(&chunk, 3);
    // write_chunk(&chunk, OP_CONSTANT, 1);
    // write_chunk(&chunk, constant, 1);

    // write_chunk(&chunk, OP_MULTIPLY, 1);

    // write_chunk(&chunk, OP_ADD, 1);

    // write_chunk(&chunk, OP_RETURN, 1);

    // 3 - 2 - 1
    // int constant = add_constant_to_chunk(&chunk, 3);
    // write_chunk(&chunk, OP_CONSTANT, 1);
    // write_chunk(&chunk, constant, 1);

    // constant = add_constant_to_chunk(&chunk, 2);
    // write_chunk(&chunk, OP_CONSTANT, 1);
    // write_chunk(&chunk, constant, 1);

    // write_chunk(&chunk, OP_SUBTRACT, 1);

    // constant = add_constant_to_chunk(&chunk, 1);
    // write_chunk(&chunk, OP_CONSTANT, 1);
    // write_chunk(&chunk, constant, 1);

    // write_chunk(&chunk, OP_SUBTRACT, 1);

    // write_chunk(&chunk, OP_RETURN, 1);

    // 1 + 2 * 3 - 4 / -5
    int constant = add_constant_to_chunk(&chunk, 1);
    write_chunk(&chunk, OP_CONSTANT, 1);
    write_chunk(&chunk, constant, 1);

    constant = add_constant_to_chunk(&chunk, 2);
    write_chunk(&chunk, OP_CONSTANT, 1);
    write_chunk(&chunk, constant, 1);

    constant = add_constant_to_chunk(&chunk, 3);
    write_chunk(&chunk, OP_CONSTANT, 1);
    write_chunk(&chunk, constant, 1);

    write_chunk(&chunk, OP_MULTIPLY, 1);

    constant = add_constant_to_chunk(&chunk, 4);
    write_chunk(&chunk, OP_CONSTANT, 1);
    write_chunk(&chunk, constant, 1);

    constant = add_constant_to_chunk(&chunk, 5);
    write_chunk(&chunk, OP_CONSTANT, 1);
    write_chunk(&chunk, constant, 1);

    write_chunk(&chunk, OP_NEGATE, 1);

    write_chunk(&chunk, OP_DIVIDE, 1);

    write_chunk(&chunk, OP_SUBTRACT, 1);

    write_chunk(&chunk, OP_ADD, 1);

    write_chunk(&chunk, OP_RETURN, 1);

    interpret(&chunk);

    free_vm();
    free_chunk(&chunk);

    return 0;
}