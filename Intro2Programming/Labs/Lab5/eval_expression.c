#include <stdio.h>
#include <math.h>

#include "utilities.h"
#include "eval_expression.h"

static float f1, f2;
static char op;

char valid_ops[] = {'+', '-', '*', '/', '^'};
int ops_s = sizeof(valid_ops) / sizeof(valid_ops[0]);

int is_valid_expression(const char *str)
{
    int i, res, valid = 0;
    char operation;

    res = sscanf(str, "%f %c %f", &f1, &operation, &f2);
    
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

float get_first_operand()
{
    return f1;
}

float get_second_operand()
{
    return f2;
}

float get_expr_value()
{
    float result;

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
        case '^':
            result = pow(f1, f2);
            break;
    }

    return result;
}
