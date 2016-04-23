#include <stdio.h>

#include "eval_expression.h"

int main()
{
    char line[256];

    while(fgets(line, sizeof(line) - 1, stdin)) {
        if(strcmp(line, "exit") == 0) {
            break;
        }

        if(is_valid_expression(line)) {
            printf("%f", get_expr_value());
        } else {
            printf("Expression error");
        }
    }

    return 0;
}
