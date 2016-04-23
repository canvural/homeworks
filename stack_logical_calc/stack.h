#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 100

typedef struct stack_ {
    int arr[STACK_SIZE];
    int top;
} Stack;

void new(Stack s);
int push(Stack *s, int el);
int pop(Stack *s);

#endif
