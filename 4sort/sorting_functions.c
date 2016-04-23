#include <stdlib.h>

#include "sorting_functions.h"

void merge (int *arr, int n, int m) {
    int i, j, k;
    int *x = malloc(n * sizeof (int));

    for (i = 0, j = m, k = 0; k < n; k++) {
        x[k] = j == n          ? arr[i++]
        : i == m          ? arr[j++]
        : arr[j] < arr[i] ? arr[j++]
        :                   arr[i++];
    }

    for (i = 0; i < n; i++) {
        arr[i] = x[i];
    }

    free(x);
}

void merge_sort (int *arr, int n) {
    if (n < 2) {
        return;
    }

    int m = n / 2;

    merge_sort(arr, m);
    merge_sort(arr + m, n - m);
    merge(arr, n, m);
}

void bubble_sort(int *arr, int n)
{
    int i, j, temp;

    for (i = 1; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void quick_sort (int *arr, int n) {
    int l, r, p, t;

    if(n < 2) {
        return;
    }

    p = arr[n / 2];
    r = n - 1;
    l = 0;

    while(1) {
        while(arr[l] < p) {
            ++l;
        }

        while(p < arr[r]) {
            r--;
        }

        if(l >= r) {
            break;
        }

        t = arr[l];
        arr[l] = arr[r];
        arr[r] = t;
        l++;
        r--;
    }

    quick_sort(arr, l);
    quick_sort(arr + l, n - l);
}

void heap(int *arr, int n)
{
    int i, t;

    for(i = n / 2; i >= 0; i--) {
        if(arr[(2 * i) + 1] < arr[(2 * i) + 2]
            && (2 * i + 1) <= n
            && (2 * i + 2) <= n
        ) {
            t = arr[(2 * i) + 1];
            arr[(2 * i) + 1] = arr[(2 * i) + 2];
            arr[(2 * i) + 2] = t;
        }

        if(arr[(2 * i) + 1] > arr[i]
            && (2 * i + 1) <= n
            && i <= n
        ) {
            t = arr[(2 * i) + 1];
            arr[(2 * i) + 1] = arr[i];
            arr[i] = t;
        }
    }
}

void heap_sort(int *arr, int n)
{
    int i, t;

    heap(arr, n);

    for(i = n - 1; i >= 1; i--)
    {
        t =  arr[i];
        arr[i] = arr[0];
        arr[0] = t;
        heap(arr, i - 1);
    }
}
