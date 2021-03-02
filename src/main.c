#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    init_chunk(&chunk);

    for (int i = 0; i < 300; i++) {
        write_constant_to_chunk(&chunk, i, (int)(i / 3));
    }

    disassemble_chunk(&chunk, "test chunk");

    free_chunk(&chunk);
    return 0;
}