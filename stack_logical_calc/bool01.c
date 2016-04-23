#include <stdio.h>

#include "stack.h"

#define MAX_EXPR_SIZE 100

int Evaluate01(char *expr);
void Evaluate02(Stack *nums, Stack *ops);

int main(int argc, char const *argv[]) {
    char expr[MAX_EXPR_SIZE + 1];

    while(1) {
        printf("Bir mantiksal ifade giriniz: ");
		scanf("%s", expr);

		printf("Bu ifadenin sonucu: ");
		printf("%d\n", Evaluate01(expr));
    }

    return 0;
}

int Evaluate01(char *expr)
{
    Stack nums, ops;

    new(nums);
    new(ops);

    int i = 0;
    char c;

    while((c = expr[i]) != '\0') {
        if(c == '(') {
            i++;
            continue;
        } else if(c == '.' || c == '+' || c == 'x' || c == '\'' || c == '>') {
            push(&ops, c - '0');
        } else if(c == '0' || c == '1') {
            push(&nums, (c - '0'));
        } else if(c == ')') {
            Evaluate02(&nums, &ops);
        } else {
            printf("\n%c is invalid..\n", c);
        }
        i++;
    }

    return pop(&nums);
}

void Evaluate02(Stack *nums, Stack *ops)
{
    char op = pop(ops) + '0';

    int num2 = pop(nums);
    int num1;

    if(op != '\'') {
        num1 = pop(nums);
    }

    int result;

    switch (op) {
        case '\'':
            result = !num2;
            break;
        case '.':
            result = num1 & num2;
            break;
        case '+':
            result = num1 | num2;
            break;
        case 'x':
            result = num1 ^ num2;
            break;
        case '>':

            break;
        default:
            printf("%c is not valid", op);
    }

    push(nums, result);
}
