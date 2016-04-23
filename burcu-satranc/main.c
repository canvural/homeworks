#include <stdio.h>

int main(int argc, char const *argv[]) {
    int tahta[8][8] = {0};
    int map[9] = {0, 7, 6, 5, 4, 3, 2, 1, 0};
    char from[3],
         to[3],
         b1[3], b2[3], s[3];

    printf("Taslarin konumlarini giriniz: \nBeyaz Kale: ");
    scanf("%2s", b1);

    printf("\nBeyaz Kale: ");
    scanf("%2s", b2);

    printf("\nSiyah Sah: ");
    scanf("%2s", s);

    // Taşları yerine koyuyoruz
    int b1_c = b1[0] - 'a';
    int b2_c = b2[0] - 'a';
    int s_c = s[0] - 'a';
    int b1_r = b1[1] - '0';
    int b2_r = b2[1] - '0';
    int s_r = s[1] - '0';

    // Kale için 1 ve 2 şah için 3
    tahta[map[b1_r]][b1_c] = 1;
    tahta[map[b2_r]][b2_c] = 2;
    tahta[map[s_r]][s_c]   = 3;

    int ilk_hamle = 1;
    int i, j;

    do {
        printf("\nHamle Girin: ");
        scanf("%2s %2s", from, to);

        int from_c = from[0] - 'a'
        ,   to_c   = to[0] - 'a'
        ,   from_r = from[1] - '0'
        ,   to_r   = to[1] - '0';

        int tas = tahta[map[from_r]][from_c];

        // Verilen yerde taş yoksa, geçersiz hamle
        if(tahta[map[from_r]][from_c] == 0) {
            printf("Gecersiz hamle");
            continue;
        }

        if(from_r == to_r && from_c == to_c) {
            printf("Gecersiz hamle");
            continue;
        }

        if(ilk_hamle) {
            if(tas != 1 && tas != 2) {
                printf("İlk hamleyi beyazin yapmasi lazim!");
                continue;
            }

            ilk_hamle = 0;
        }

        // Kale için hareketin kontrolü
        if(tas == 1 || tas == 2) {
            if(from_r != to_r && from_c != to_c) {
                printf("Gecersiz hamle");
                continue;
            }
        } else if(tas == 3) {
            // Şah için hareket kontrolü
            if((to_r - from_r) > 1 || (to_c - from_c) > 1) {
                printf("Gecersiz hamle");
                continue;
            }

            int hata = 0;

            for(i = 0; i < 8; i++) {
                if(tahta[map[to_r]][i] == 1 || tahta[map[to_r]][i] == 2
                    || tahta[i][to_c] == 1 || tahta[i][to_c] == 2) {
                    hata = 1;
                    break;
                }
            }

            if(hata) {
                printf("Gecersiz hamle");
                continue;
            }
        }

        // Hareketi yap
        tahta[map[from_r]][from_c] = 0;
        tahta[map[to_r]][to_c] = tas;

        if(tas == 1) {
            b1_c = to_c;
            b1_r = to_r;
        } else if(tas == 2) {
            b2_c = to_c;
            b2_r = to_r;
        } if(tas == 3) {
            s_c = to_c;
            s_r = to_r;
        }

        printf("Tas konumları: Kale1: %c%d, Kale2: %c%d, Sah: %c%d\n",
            b1_c  + 'a', b1_r,
            b2_c  + 'a', b2_r,
            s_c   + 'a', s_r
        );

        // Mat kontrolü
        int mat = 0;
        int f = 0;
        if(map[s_r] > 0) {
            for(i = 0; i < 8; i++) {
                if(tahta[map[s_r] - 1][i] == 1
                    || tahta[map[s_r] - 1][i] == 2) {
                    mat++;
                    break;
                }
            }
        } else {
            f++;
        }

        if(map[s_r] < 7) {
            for(i = 0; i < 8; i++) {
                if(tahta[map[s_r] + 1][i] == 1
                    || tahta[map[s_r] + 1][i] == 2) {
                    mat++;
                    break;
                }
            }
        } else {
            f++;
        }

        for(i = 0; i < 8; i++) {
            if(tahta[map[s_r]][i] == 1
                || tahta[map[s_r]][i] == 2) {
                    mat++;
                    break;
                }
        }

        if(mat >= (3 - f)) {
            printf("Mat\n");
            break;
        }
    } while(1);

    return 0;
}
