#include <stdio.h>

#include "stack.h"

#define MAX_EXPR_SIZE 100

int EvaluatePQ(char *expr, int p, int q);
void Evaluate02(Stack *nums, Stack *ops);

int main(int argc, char *argv[]) {

	char expr[MAX_EXPR_SIZE+1];
	int p, q, result;

	while(1) {

		printf("Bir mantiksal ifade giriniz: ");
		scanf("%s", expr);

		printf("p q sonuc\n");
		printf("- - -----\n");
		printf("0 0 %d\n", EvaluatePQ(expr,0,0));
		printf("0 1 %d\n", EvaluatePQ(expr,0,1));
		printf("1 0 %d\n", EvaluatePQ(expr,1,0));
		printf("1 1 %d\n", EvaluatePQ(expr,1,1));
	}

	return 0;
}

int EvaluatePQ(char *expr, int p, int q)
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
        } else if(c == 'p') {
            push(&nums, p);
        } else if(c == 'q') {
            push(&nums, q);
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
            result = !(num1 > num2);
            break;
        default:
            printf("%c is not valid", op);
    }

    push(nums, result);
}
