#include <stdio.h>

int main(int argc, char const *argv[]) {
    int k, sayi,
        size = 100;

    int *array = malloc(size * sizeof(int));
    if(NULL == array) {
        printf("Can't allocate memory");
        return 1;
    }

    printf("k: ");
    scanf("%d", &k);

    if(k >= 100) {
        printf("\nk 100 den kucuk olmali");
        return 1;
    }

    int i = 1, j;
    int max = 0;
    int m;

    while(1) {
        if(i == size) {
            size *= 2;
            array = realloc(array, size * sizeof(int));
        }

        printf("[%d] Bir sayi giriniz: ");
        scanf("%d", &m);

        if(m > max) {
            max = m;
        }

        array[i - 1] = m;

        for(j = 0; j < i; j++) {
            printf("");
        }

        i++;
    }

    return 0;
}
