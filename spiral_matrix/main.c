#include <stdio.h>
#include <stdlib.h>

void matrix_yaz(int boyut, int matrix[][boyut]);
void matrix_doldur(int boyut, int matrix[][boyut]);

int main(int argc, char const *argv[]) {

    int matrix_boyut = 0;
    int i;

    while(1) {
        printf("Lutfen boyutu giriniz, programdan çıkmak için -1 giriniz: ");
        scanf("%d", &matrix_boyut);

        if(matrix_boyut == -1) {
            break;
        }

        int matrix[matrix_boyut][matrix_boyut];

        matrix_doldur(matrix_boyut, matrix);
        matrix_yaz(matrix_boyut, matrix);
    }

    printf("Gule gule");

    return 0;
}

void matrix_yaz(int boyut, int matrix[][boyut])
{
    int i, j;

    for(i = 0; i < boyut; i++) {
        for(j = 0; j < boyut; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

void matrix_doldur(int boyut, int matrix[][boyut])
{
    int i = 0,
        j = 0,
        c = 0,
        k = 0;

    for(i = boyut - 1 , j = 0 ; i >= 0 ; i--, j++) {
        // Soldan sağa doldur
        for(k = j ; k <= i; k++) {
            matrix[j][k] = c;
        }

        c++;
        if(c > 9) {
            c = 0;
        }

        // Yukardan aşağı doldur
        for(k = j + 1 ; k <= i; k++) {
            matrix[k][i] = c;
        }

        c++;
        if(c > 9) {
            c = 0;
        }

        // Sağdan sola doldur
        for(k = i - 1 ; k >= j; k--) {
            matrix[i][k] = c;
        }

        c++;
        if(c > 9) {
            c = 0;
        }

        // Aşağıdan yukarı doldur
        for(k = i - 1 ; k > j; k--) {
            matrix[k][j] = c;
        }

        c++;
        if(c > 9) {
            c = 0;
        }
    }
}
