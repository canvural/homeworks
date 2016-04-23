#include <stdio.h>

int main(int argc, char const *argv[]) {
    int i, sayi, b;

    printf("Tam sayi degeri giriniz:");
    scanf("%d", &sayi);

    for (i = 0; i < sayi; i++) {
        if(i % 4 == 0) {
            b++;
        }
    }

    printf("4 ile bolunen sayi adedi: %d", b);

    return 0;
}
