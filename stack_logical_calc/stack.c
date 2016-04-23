#include "stack.h"

void new(Stack s)
{
    s.top = -1;
}

int push(Stack *s, int el)
{
    if(s->top < STACK_SIZE) {
        s->arr[++s->top] = el;
        return 1;
    }

    return 0;
}

int pop(Stack *s)
{
    if(s->top >= 0) {
        return s->arr[s->top--];
    }

    return -1;
}
