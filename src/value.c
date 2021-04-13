#include <stdio.h>
#include <string.h>

#include "object.h"
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
        case VAL_OBJ: print_object(value); break;
    }
}

bool values_equal(Value left, Value right) {
    if (left.type != right.type) return false;
    switch (left.type) {
        case VAL_BOOL: return AS_BOOL(left) == AS_BOOL(right);
        case VAL_NIL: return true;
        case VAL_NUMBER: return AS_NUMBER(left) == AS_NUMBER(right);
        case VAL_OBJ: {
            ObjString *left_string = AS_STRING(left);
            ObjString *right_string = AS_STRING(right);
            return left_string->length == right_string->length
                && memcmp(
                    left_string->chars,
                    right_string->chars,
                    left_string->length
                ) == 0;
        }
        default: return false; // unreachable
    }
}