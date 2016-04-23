#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Rakam {
	int rakam;
	struct _Rakam *sonraki;
} Rakam;

typedef struct {
	char sign; /* pozitif mi negatif mi */
	Rakam *rakamlar;
} BagliBuyukSayi;

BagliBuyukSayi *bosBagliBuyukSayi();
BagliBuyukSayi *yapBagliBuyukSayi(int sayi);
void yazBagliBuyukSayi(BagliBuyukSayi *sayi);
BagliBuyukSayi *yapBagliBuyukSayiText(const char *sayi);
BagliBuyukSayi *toplaBagliBuyukSayi(BagliBuyukSayi *a, BagliBuyukSayi *b);
void tersBagliBuyukSayi(BagliBuyukSayi **sayi);

int main()
{
	BagliBuyukSayi *a, *b, *c, *d, *e, *f; 

	a= yapBagliBuyukSayi(123); 

	yazBagliBuyukSayi(a); 

	printf(" + "); 

	b= yapBagliBuyukSayi(904); 

	yazBagliBuyukSayi(b); 

	printf(" = "); 

	c = toplaBagliBuyukSayi(a,b); 

	yazBagliBuyukSayi(c); 

	printf("\n"); 

	d= yapBagliBuyukSayiText("123456789123456789");
	yazBagliBuyukSayi(d);

	printf(" + "); 

	e= yapBagliBuyukSayiText("76543210876543210");
	yazBagliBuyukSayi(e);

	f = toplaBagliBuyukSayi(d,e); 

	printf(" = "); 

	yazBagliBuyukSayi(f); 

	printf("\n");

	return 0;
}

BagliBuyukSayi *bosBagliBuyukSayi()
{
	BagliBuyukSayi *sayi = malloc(sizeof(BagliBuyukSayi *));
	if(NULL == sayi) {
		printf("(bosBagliBuyukSayi) Bellek ayrılamadı!");
		exit(1);
	}

	sayi->rakamlar = NULL;

	return sayi;
}

BagliBuyukSayi *yapBagliBuyukSayi(int sayi)
{
	Rakam *suan, *ilk = NULL;

	BagliBuyukSayi *b = bosBagliBuyukSayi();

	if(sayi < 0) {
		b->sign = -1;
	} else {
		b->sign = 0;
	}

	while(sayi) {
		int basamak = sayi % 10;

		suan = malloc(sizeof(Rakam));
		if(NULL == suan) {
			printf("(yapBagliBuyukSayi) Bellek ayrılamadı!");
			exit(1);
		}

		suan->rakam = basamak;
		suan->sonraki = ilk;
		ilk = suan;

		sayi /= 10;
	}

	b->rakamlar = ilk;

	return b;
}

BagliBuyukSayi *yapBagliBuyukSayiText(const char *sayi)
{
	int i, j, k;

	Rakam *suan, *ilk = NULL;

	BagliBuyukSayi *b = bosBagliBuyukSayi();

	if(sayi[0] == '-') {
		b->sign = -1;
		k = 1;
	} else {
		b->sign = 0;
		k = 0;
	}

	int kac_basamak = strlen(sayi);

	for(i = (kac_basamak - 1); i >= k; i--) {
		/* sayıya çevirelim */
		j = sayi[i] - '0';

		suan = malloc(sizeof(Rakam));
		if(NULL == suan) {
			printf("(yapBagliBuyukSayiText) Bellek ayrılamadı!");
			exit(1);
		}

		suan->rakam = j;
		suan->sonraki = ilk;
		ilk = suan;
	}

	/* Rakamları gösteren sıralı listenin başını verelim */
	b->rakamlar = ilk;

	return b;
}

BagliBuyukSayi *toplaBagliBuyukSayi(BagliBuyukSayi *a, BagliBuyukSayi *b)
{
	BagliBuyukSayi *t = bosBagliBuyukSayi();

	int elde = 0;

	/* Toplamaya en sondan başlandığı için listeyi ters çeviriyoruz */
	tersBagliBuyukSayi(&a);
	tersBagliBuyukSayi(&b);

	Rakam *sonuc = malloc(sizeof(Rakam));
	sonuc->rakam = -1;

	while((a->rakamlar != NULL) || (b->rakamlar != NULL)){
        if(a->rakamlar != NULL){
            elde = elde + (a->rakamlar->rakam);
            a->rakamlar = a->rakamlar->sonraki;
        }
        if(b->rakamlar != NULL){
            elde = elde + (b->rakamlar->rakam);
            b->rakamlar = b->rakamlar->sonraki;
        }
        int eldee = elde / 10;
        int artan = elde % 10;
        
        Rakam *temp = malloc(sizeof(Rakam));
	    temp->rakam = artan;
	    temp->sonraki = sonuc->rakam == -1 ? NULL : sonuc;
	    sonuc = temp;

        elde = eldee;
    }

    if(elde != 0) {
    	Rakam *temp = malloc(sizeof(Rakam));
	    temp->rakam = elde;
	    temp->sonraki = sonuc;
	    sonuc = temp;
    }

    t->rakamlar = sonuc;
	
	return t;
}

void yazBagliBuyukSayi(BagliBuyukSayi *sayi)
{
	Rakam *suan = sayi->rakamlar;

	if(sayi->sign == -1) {
		printf("-");
	}

	while(suan) {
		printf("%d", suan->rakam);
		suan = suan->sonraki;
	}
}

void tersBagliBuyukSayi(BagliBuyukSayi **sayi)
{
	Rakam *eskia = (*sayi)->rakamlar;
    Rakam *yenia = NULL;
    
    while(eskia)
    {
        Rakam *eskiSonraki = eskia->sonraki;
        eskia->sonraki = yenia;
        yenia = eskia;
        
        eskia = eskiSonraki;
    }
    
    (*sayi)->rakamlar = yenia;
}