#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {

    char siir[] = "Gonul gurbet ele varma\nYa gelir ya gelinmez\nHer guzele meyil verme\nYa sevilir ya sevilmez\n\nYogruktur bizim atimiz\nYardan atlatti zatimiz\nGurbet ilde kiymatimiz\nYa bilinir ya bilinmez\n";
    int siir_len = strlen(siir),
        i, j = 0,
        dortluk_sayisi = 1,
        satir_sayisi = 0,
        kelime_sayisi = 0,
        benzersiz_kelime_sayisi = 0,
        karakter_sayisi = 0;

    char kelimeler[30][30] = {0};

    for(i = 0; i < siir_len; i++) {
        if(siir[i] == '\n' && siir[i + 1] == '\n') {
            dortluk_sayisi++;
        }

        if(siir[i] == '\n') {
            satir_sayisi++;
        }

        if(siir[i] == ' ' || (siir[i] == '\n' && siir[i + 1] != '\n')) {
            kelime_sayisi++;
            j = 0;
        }

        if(isalpha(siir[i])) {
            kelimeler[kelime_sayisi][j] = siir[i];
            j++;
            karakter_sayisi++;
        }
    }

    int b = 0;

    for(i = 0; i < kelime_sayisi; i++) {
        b = 1;
        for (j = 0; b && j < i; j++) {
            if(strcasecmp(kelimeler[i], kelimeler[j]) == 0) {
                b = 0;
            }
        }

        if(b) {
            benzersiz_kelime_sayisi++;
        }
    }

    double bosluksuz_satir_sayisi = dortluk_sayisi * 4;

    printf("Dortluk sayisi: %d\nSatir Sayisi: %d\nKelime sayisi: %d\nBenzersiz Kelime sayisi: %d\nSatır başına kelime: %f\nToplam Karakter: %d", dortluk_sayisi, satir_sayisi, kelime_sayisi, benzersiz_kelime_sayisi, (kelime_sayisi / bosluksuz_satir_sayisi), karakter_sayisi);

    return 0;
}
