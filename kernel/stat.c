#include <stdio.h>
#include <math.h>

#include "stat.h"

int minimum(int array[], int n)
{
    int min = array[0], i;

    for(i = 1; i < n; i++)
        if(array[i] < min)
            min = array[i];

    return min;

}
int maximum(int array[], int n)
{
    int max = array[0], i;

    for(i = 1; i < n; i++) {
        if(array[i] > max) {
            max = array[i];
        }
    }

    return max;
}

float average(int array[], int n)
{
    float avg = 0.0;
    int i;

    for(i = 0; i < n; i++) {
        avg += array[i];
    }

    return avg / n;
}

float stddev(int array[], int n)
{
    float avg = average(array, n);

    int i;
    float sum;

    for(i = 0; i < n; i++) {
        sum += pow((array[i] - avg), 2);
    }

    return sqrt(sum / (float) n);
}
