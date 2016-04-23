#include <stdio.h>

#include "eval_expression.h"

int main(int argc, char const *argv[]) {
    if(argc < 2) {
        // Expects a switch
        return 1;
    }

    char line[256];

    while(fgets(line, sizeof(line) - 1, stdin)) {
        int valid = is_valid_expression(line);

        switch (argv[1][1]) {
            case 'E':
                if(!valid) {
                    printf("%s", line);
                }

                break;
            case 'V':
                if(valid) {
                    printf("%f", get_expr_value());
                }

                break;
        }
    }

    return 0;
}
