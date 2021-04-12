#include <stdio.h>

#include "memory.h"
#include "value.h"

void init_value_array(ValueArray *array) { 
    array->count = 0;
    array->capacity = 0;
    array->values = NULL;
}

void free_value_array(ValueArray *array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    init_value_array(array);
}

void write_value_array(ValueArray *array, Value value) {
    if (array->capacity < array->count + 1) {
        int capacity_old = array->capacity;
        array->capacity = GROW_CAPACITY(capacity_old);
        array->values = GROW_ARRAY(
            Value, array->values, 
            capacity_old, array->capacity
        );
    }
    array->values[array->count] = value;
    array->count++;
}

void print_value(Value value) {
    switch (value.type) {
        case VAL_BOOL:
            printf(AS_BOOL(value) ? "true" : "false");
            break;
        case VAL_NIL: printf("nil"); break;
        case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
    }
    printf("%g", AS_NUMBER(value));
}