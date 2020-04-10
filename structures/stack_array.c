// implementation of integer stack using array 

#include <stdio.h>
#include <stdlib.h>

typedef struct stackArray {
    int currentIndex;
    int capacity;
    int *array;
}
stackArray;

struct stackArray *newStack(int capacity);
void push(stackArray *stack, int data);
int pop(stackArray *stack);
int peek(stackArray *stack);

int main(void) {
    stackArray *stack = newStack(50);

    push(stack, 10);
    push(stack, 12);
    push(stack, 15);
    printf("%d\n", stack->array[0]);
    printf("%d\n", peek(stack));
    printf("%d\n", stack->array[1]);
    printf("%d\n", stack->array[2]);
    printf("%d\n", pop(stack));
    printf("%d\n", pop(stack));
    printf("%d\n", pop(stack));
    printf("%d\n", pop(stack));

    free(stack->array);
    free(stack);
}

stackArray *newStack(int capacity) {
    int *array = malloc(capacity * sizeof(int));
    stackArray *stack = malloc(sizeof(stackArray));
    stack->currentIndex = 0;
    stack->capacity = capacity;
    stack->array = array;
    return stack;
}


void push(stackArray *stack, int data) {
    if(stack->currentIndex < stack->capacity) {
        stack->array[stack->currentIndex] = data;
        stack->currentIndex++;
    }
}

int pop(stackArray *stack) {
    if (stack->currentIndex <= 0) {
        return -1234567;
    }
    stack->currentIndex--;
    return stack->array[stack->currentIndex];
}

int peek(stackArray *stack) {
    return stack->array[stack->currentIndex];
}