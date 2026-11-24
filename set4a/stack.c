#include <stdlib.h>
#include "stack.h"

struct Stack {
    int *values;
    int size;
    int capacity;
};

Stack* stack_create(void) {
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL) return NULL;

    stack->values = malloc(4 * sizeof(int));
    if (stack->values == NULL) {
        free(stack);
        return NULL;
    }

    stack->size = 0;
    stack->capacity = 4;
    return stack;

}

void stack_push(Stack *stack, int value) {
    if (stack->size == stack->capacity) {
        int new_capacity = stack->capacity * 2;
        int *new_values = realloc(stack->values,
                                  new_capacity * sizeof(int));
        if (new_values == NULL) return;
        stack->values = new_values;
        stack->capacity = new_capacity;
    }
    stack->values[stack->size] = value;
    stack->size++;
}

void stack_pop(Stack *stack) {
    stack->size--;
}

int stack_top(Stack *stack) {
    return stack->values[stack->size - 1];
}

int stack_size(Stack *stack) {
    return stack->size;
}

void stack_free(Stack *stack) {
    free(stack->values);
    free(stack);
}
