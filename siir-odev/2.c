#include <stdio.h>

int main(int argc, char const *argv[]) {
    int x;

    printf("X degerini giriniz:");
    scanf("%d", &x);

    printf("f(x) = ");
    if(x < 0) {
        printf("%d", x);
    } else if(x > 1 && x < 10) {
        printf("%d", x*x);
    } else if(x > 11 && x < 100) {
        printf("%d", x*x + x);
    } else if(x >= 100) {
        printf("%d", x*x + (2*x) + 5);
    }

    return 0;
}
