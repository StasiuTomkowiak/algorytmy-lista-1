#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

void enqueue(Queue *q, int value) {
    if ((q->rear + 1) % MAX_SIZE == q->front) {
        printf("Queue is full!\n");
        return;
    }
    else if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    }
    else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    q->data[q->rear] = value;
}

int dequeue(Queue *q) {
    int value;
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    else if (q->front == q->rear) {
        value = q->data[q->front];
        q->front = -1;
        q->rear = -1;
    }
    else {
        value = q->data[q->front];
        q->front = (q->front + 1) % MAX_SIZE;
    }
    return value;
}

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initializeStack(Stack *s) {
    s->top = -1;
}

int isStackEmpty(Stack *s) {
    return (s->top == -1);
}

void push(Stack *s, int value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack is full!\n");
        return;
    }
    s->top++;
    s->data[s->top] = value;
}

int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty!\n");
        exit(1);
    }
    return s->data[s->top--];
}

int main() {
    Queue q;
    Stack s;

    initializeQueue(&q);
    initializeStack(&s);

    for (int i = 1; i <= 50; i++) {
        enqueue(&q, i);
        printf("Dodano do kolejki: %d\n", i);
        push(&s, i);
        printf("Dodano do stosu: %d\n", i);
    }

    printf("\n--- Pobieranie elementów z kolejki ---\n");
    while (!isEmpty(&q)) {
        int item = dequeue(&q);
        printf("Wyjęto z kolejki: %d\n", item);
    }

    printf("\n--- Pobieranie elementów ze stosu ---\n");
    while (!isStackEmpty(&s)) {
        int item = pop(&s);
        printf("Wyjęto ze stosu: %d\n", item);
    }

    return 0;
}
