#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    init_chunk(&chunk);

    int constant = add_constant_to_chunk(&chunk, 1.2);
    write_chunk(&chunk, OP_CONSTANT, 123);
    write_chunk(&chunk, constant, 123);

    write_chunk(&chunk, OP_RETURN, 123);

    int const2 = add_constant_to_chunk(&chunk, 99);
    write_chunk(&chunk, OP_CONSTANT, 124);
    write_chunk(&chunk, const2, 124);

    write_chunk(&chunk, OP_RETURN, 125);
    write_chunk(&chunk, OP_RETURN, 125);

    disassemble_chunk(&chunk, "test chunk");

    free_chunk(&chunk);
    return 0;
}