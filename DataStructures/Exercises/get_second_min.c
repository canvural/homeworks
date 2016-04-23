#include <stdio.h>

int get_second_min(int *arr, int size)
{
    int i,
        min    = arr[0],
        second = 999;
        
    for(i = 1; i < size; i++) {
        if(arr[i] < min) {
            second = min;
            min = arr[i];
        } else if(arr[i] != min && arr[i] < second) {
            second = arr[i];
        }
    }
    
    return second;
}

int main(void) {
    int array[] = {2,2,15,3,3};
    
    printf("%d", get_second_min(array, 5));
    return 0;
}

