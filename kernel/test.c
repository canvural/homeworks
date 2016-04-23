#include <stdio.h>

#include "stat.h"

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("Please specify file name to read numbers!");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(!f) {
        perror("Can't open file ");
        return 1;
    }

    int n;
    // Read the first line
    fscanf(f, "%d", &n);

    int arr[n];
    int i = 0;

    while(!feof(f)) {
        fscanf(f, "%d", &arr[i]);
        i++;
    }

    int minVal = minimum(arr, n);
    printf("The minimum = %d\n", minVal);
    int maxVal = maximum(arr, n);
    printf("The maximum = %d\n", maxVal);
    float avg = average(arr, n);
    printf("The average = %.2f\n", avg);
    float std = stddev(arr, n);
    printf("The standard deviation = %.2f\n", std);

    return 0;
}
