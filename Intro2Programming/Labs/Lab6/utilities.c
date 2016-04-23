#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"

int in_array(int val, char *arr, int size)
{
    int i;

    for(i = 0; i < size; i++) {
        if(arr[i] == val) {
            return 1;
        }
    }

    return 0;
}

long int convert_to_long(char *str)
{
    int base = 0;

    if(str[0] == 'B') {
        str++;
        base = 2;
    }

    return strtol(str, NULL, base);
}

void print_result(long int i)
{
    printf("[%ld, %02lo, 0x%lx, ", i, i, i);

    print_in_binary(i);

    printf("]\n");
}

void print_in_binary(long int i)
{
    if (i > 1)
        print_in_binary(i / 2);

    printf("%ld", i % 2);
}
