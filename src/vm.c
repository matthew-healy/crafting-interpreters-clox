#include <stdio.h>
#include "common.h"
#include "debug.h"
#include "memory.h"
#include "vm.h"

VM vm;

static void reset_stack() {
    vm.stack_count = 0;
    vm.stack_capacity = 0;
    vm.stack = NULL;
}

void init_vm() {
    reset_stack();
}

void free_vm() {}

static InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    #define BINARY_OP(op)     \
        do {                  \
            double b = pop(); \
            double a = pop(); \
            push(a op b);    \
        } while (false)

    for (;;) {

        #ifdef DEBUG_TRACE_EXECUTION
            printf("          ");
            for (int i = 0; i < vm.stack_count; i++) {
                printf("[ ");
                print_value(vm.stack[i]);
                printf(" ]");
            }
            printf("\n");
            disassemble_instruction(
                vm.chunk,
                (int)(vm.ip - vm.chunk->code)
            );
        #endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD: BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE: BINARY_OP(/); break;
            case OP_NEGATE: vm.stack[vm.stack_count - 1] = (-vm.stack[vm.stack_count - 1]); break;
            case OP_RETURN: {
                print_value(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

    #undef BINARY_OP
    #undef READ_CONSTANT
    #undef READ_BYTE
}

InterpretResult interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}

void push(Value value) {
    if (vm.stack_capacity < vm.stack_count + 1) {
        int capacity_old = vm.stack_capacity;
        vm.stack_capacity = GROW_CAPACITY(capacity_old);
        vm.stack = GROW_ARRAY(
            Value, vm.stack,
            capacity_old, vm.stack_capacity
        );
    }
    vm.stack[vm.stack_count] = value;
    vm.stack_count++;
}

Value pop() {
    vm.stack_count--;
    return vm.stack[vm.stack_count];
}