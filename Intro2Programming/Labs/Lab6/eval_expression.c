#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utilities.h"
#include "eval_expression.h"

static long int f1, f2;
static char op;

char valid_ops[] = {'+', '-', '*', '/', '%', '<', '>', '&', '|', '^'};
int ops_s = sizeof(valid_ops) / sizeof(valid_ops[0]);

int is_valid_expression(const char *str)
{
    int i, res, valid = 0;
    char first[33], second[33];
    char operation;

    res = sscanf(str, "%32s %c %32s", first, &operation, second);

    f1 = convert_to_long(first);
    f2 = convert_to_long(second);

    if(!in_array(operation, valid_ops, ops_s)) {
        return 0;
    }

    op = operation;

    return res == 3;
}

int get_operator()
{
    return op;
}

long int get_first_operand()
{
    return f1;
}

long int get_second_operand()
{
    return f2;
}

long int get_expr_value()
{
    long int result;

    switch(op) {
        case '+':
            result = f1 + f2;
            break;
        case '-':
            result = f1 - f2;
            break;
        case '*':
            result = f1 * f2;
            break;
        case '/':
            result = f1 / f2;
            break;
        case '%':
            result = f1 % f2;
            break;
        case '<':
            result = f1 << f2;
            break;
        case '>':
            result = f1 >> f2;
            break;
        case '&':
            result = f1 & f2;
            break;
        case '|':
            result = f1 | f2;
            break;
        case '^':
            result = f1 ^ f2;
            break;
    }

    return result;
}
