#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *initArray(int sizeDimension1, int sizeDimension2, int sizeDimension3);
int *getCell(int *array, int indexDimension1, int indexDimension2, int indexDimension3);

#define NROWS  10
#define NCOLS  50
#define NDEPTH 20

int main()
{
    int *array = initArray(NROWS, NCOLS, NDEPTH);
    if(NULL == array) {
        perror("Malloc failed: ");
        return 1;
    }

    int array_size = NROWS * NCOLS * NDEPTH;

    // To fill the array with 0
    memset(array, 0, array_size);

    // Fill the array
    int i, j, k, l = 0;

    for(i = 0; i < NROWS; i++)
        for(j = 0; j < NCOLS; j++)
            for(k = 0; k < NDEPTH; k++) {
                int *cell = getCell(array, i, j, k);
                l++;
                *cell = l;
            }

    // Read all the cells and get sum of numbers

    unsigned long int sum = 0;

    for(i = 0; i < NROWS; i++)
        for(j = 0; j < NCOLS; j++)
            for(k = 0; k < NDEPTH; k++)
                sum += *(getCell(array, i, j, k));

    int expected_sum = (array_size * (array_size + 1) / 2);

    if(sum == expected_sum) {
        printf("Program is correct!");
    } else {
        printf("Program failed!");
    }

    printf("\nArray size: %d\n", array_size);
    printf("Sum of all numbers: %ld", sum);

    free(array);

    return 0;
}

int *initArray(int sizeDimension1, int sizeDimension2, int sizeDimension3)
{
    int *array = malloc((sizeDimension1 * sizeDimension2 * sizeDimension3) * sizeof(int));

    return array;
}

int *getCell(int *array, int indexDimension1, int indexDimension2, int indexDimension3)
{
    return &(array[indexDimension3 * NROWS * NCOLS + indexDimension2 * NROWS + indexDimension1]);
}
