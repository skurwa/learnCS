// implementation of queue using linked list 

#include <stdio.h>
#include <stdlib.h>

typedef struct queueNode {
    int  data;
    struct queueNode *next;
}
queueNode;

typedef struct queue {
    struct queueNode *in;
    struct queueNode *out;
} queue;

struct queue* makeQueue(void);
void enqueue(queue* q, int data);
int dequeue(queue* q);
int peek(queue* q);

int main(void) {
    queue* q = makeQueue();
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);

    printf("%d\n", dequeue(q));
    printf("%d\n", peek(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", peek(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", peek(q));
    enqueue(q, 12);
    printf("%d\n", dequeue(q));
    printf("%d\n", peek(q));
    free(q);
}

struct queue* makeQueue(void) {
    queue *q = malloc(sizeof(queue));
    q->in = NULL;
    q->out = NULL;
    return q;
}

void enqueue(queue* q, int data) {
    queueNode *tmp = malloc(sizeof(queueNode));
    if (tmp != NULL) {
        tmp->data = data;
        tmp->next = NULL;
        if (q->in != NULL) {
            q->in->next = tmp;
        }
        if (q->out == NULL) {
            q->out = tmp;
        }
        q->in = tmp;

    }
}

int dequeue(queue* q) {
    if (q->in == q->out) {
        q->in = NULL;
    }
    if (q->out == NULL) {
        return -1234567;
    }
    queueNode *tmp = q->out;
    int outData = tmp->data;
    q->out = tmp->next;
    free(tmp);
    return outData;   
}

int peek(queue* q) {
    if (q->out == NULL) {
        return -123456789;
    }
    return q->out->data;
}