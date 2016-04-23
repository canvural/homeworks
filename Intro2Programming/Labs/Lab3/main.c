#include <stdio.h>

#include "func.h"

int main(int argc, const char *argv[]) {

    char line[256];

    while(fgets(line, sizeof(line) - 1, stdin)) {
        if(argc < 2) {
            count_most_often_occurences(line);
        }

        
    }

    return 0;
}
