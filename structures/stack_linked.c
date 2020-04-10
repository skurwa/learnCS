// implementation of integer stack using linked list 

#include <stdio.h>
#include <stdlib.h>

typedef struct stackNode {
    int  data;
    struct stackNode *next;
}
stackNode;

struct stackNode *newNode(int data);
void push(stackNode **stack, int data);
int pop(stackNode **stack);
int peek(stackNode *stack);

int main(void) {
    stackNode *stack = NULL;
    push(&stack, 2);
    printf("%d\n", stack->data);
    push(&stack, 5);
    printf("%d\n", stack->data);
    printf("%d\n", pop(&stack));
    printf("%d\n", peek(stack));
    printf("%d\n", pop(&stack));
    printf("%d\n", pop(&stack));
    printf("%d\n", pop(&stack));
    printf("%d\n", peek(stack));
    free(stack);
}

struct stackNode *newNode(int data) {
    stackNode *stack = malloc(sizeof(stackNode));
    if (stack != NULL) {
        stack->data = data;
        stack->next = NULL;
    }
    return stack;    
}

void push(stackNode **stack, int data) {
    stackNode *new = newNode(data); 
    new->next = *stack;
    *stack = new;
}

int pop(stackNode **stack) {
    if (*stack == NULL) {
        return -1234567;
    }
    stackNode *tmp = *stack;
    *stack = tmp->next;
    int popped = tmp->data;
    free(tmp);
    return(popped);     
}

int peek(stackNode *stack) {
    if (stack == NULL) {
        return -1234567;
    }
    return stack->data;
}