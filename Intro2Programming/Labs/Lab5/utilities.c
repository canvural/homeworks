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
