#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "sorting_functions.h"

int main(int argc, char const *argv[]) {
    char *files[] = {
        "unsortedArray0100.dat",
        "unsortedArray0200.dat",
        "unsortedArray0300.dat",
        "unsortedArray0400.dat",
        "unsortedArray0500.dat",
        "unsortedArray0600.dat",
        "unsortedArray0700.dat",
        "unsortedArray0800.dat",
        "unsortedArray0900.dat",
        "unsortedArray1000.dat"
    };

    char *algorithms[] = {
        "BubbleSorted",
        "QuickSorted",
        "HeapSorted",
        "MergeSorted"
    };

    char *output_files[] = {
        "bubbleSorted.dat",
        "quickSorted.dat",
        "heapSorted.dat",
        "mergeSorted.dat"
    };

    int i, j, k;

    for(k = 0; k < 4; k ++) {
        for (i = 0; i < 10; i++) {
            int size = (i + 1) * 100;

            int *arr = read_from_file(files[i], size);
            if(NULL == arr) {
                return 1;
            }

            start_timer();

            printf("Unsorted Array:\n");

            for (j = 0; j < size; j++) {
                printf("%d%s", arr[j], j == size - 1 ? "\n" : " ");
            }

            run_algorithm(k, arr, size);
            printf("%s Array %d Elements\n", algorithms[k], size);

            for (j = 0; j < size; j++) {
                printf("%d%s", arr[j], j == size - 1 ? "\n" : " ");
            }

            double elapsedTime = stop_timer();
            printf("Elapsed time: %lf ms.\n", elapsedTime );

            FILE *out = fopen(output_files[k], "a+");
            fwrite(arr, sizeof(int), size, out);
            fclose(out);

            free(arr);
        }
    }

    return 0;
}

void run_algorithm(int k, int *arr, int size)
{
    switch (k) {
        case 0:
            bubble_sort(arr, size);
            break;
        case 1:
            quick_sort(arr, size);
            break;
        case 2:
            heap_sort(arr, size);
            break;
        case 3:
            merge_sort(arr, size);
            break;
    }
}

int *read_from_file(char *file_name, int size)
{
    int *arr = malloc(sizeof(int) * size);
    if(NULL == arr) {
        printf("Can't allocate memory\n");
        return NULL;
    }

    FILE *f = fopen(file_name, "r");
    if(NULL == f) {
        printf("Can't open file!");
        return NULL;
    }

    if(fread(arr, sizeof(int), size, f) != size) {
        printf("Read error!");
        return NULL;
    }

    fclose(f);

    return arr;
}

#ifdef _WIN_32
void start_timer()
{
    // get ticks per second
    QueryPerformanceFrequency(&frequency);

    // start timer
    QueryPerformanceCounter(&t1);
}

double stop_timer()
{
    // stop timer
    QueryPerformanceCounter(&t2);

    // compute and print the elapsed time in millisec
    return (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
}
#endif
