#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 20

typedef struct StackDataType_ {
	char tahta[3][3];
	int islem;
}StackDataType;

struct STACK{
	StackDataType element[STACKSIZE];
	int top;
};

typedef struct STACK Stack;

Stack yigin1, yigin2;

void create();
void close();
int push();
StackDataType pop();
int isempty();

int compare(StackDataType *x, StackDataType hedef);
int compare2(StackDataType x, StackDataType hedef);
void add(Stack s, StackDataType *e);

int main()
{
	create(yigin1);
	create(yigin2);

	int a, b, c, i, j, k = 0, adim = 0;

	int satir, sutun;

	StackDataType baslangic, hedef;
	StackDataType *yeni;

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			hedef.tahta[i][j] = k++;
		}
	}

	FILE *f = fopen("baslangic.txt", "r");
	if(!f) {
		printf("Dosya bulunamadı!\n");
		exit(1);
	}

	i = 0;
	while(!feof(f)) {
		fscanf(f, "%d %d %d", &a, &b, &c);
		baslangic.tahta[i][0] = a;
		baslangic.tahta[i][1] = b;
		baslangic.tahta[i][2] = c;
		i++;
	}

	printf("BASLANGIC\n\n");

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			printf("%d ", baslangic.tahta[i][j]);
		}
		printf("\n");
	}

	printf("\nHEDEF\n\n");

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			printf("%d ", hedef.tahta[i][j]);
		}
		printf("\n");
	}

	push(&yigin1, baslangic);

	while(!isempty(yigin1)) {
		StackDataType x = pop(&yigin1);
		push(&yigin2, x);

		for(i = 0; i < 3; i++) {
			for(j = 0; j < 3; j++) {
				if(x.tahta[i][j] == 0) {
					satir = i;
					sutun = j;
					break;
				}
			}
		}

		if(compare2(x, hedef)) {
			printf("COZUM ADIMLARI:\n\n");
			for(i = 0; i < yigin2.top; i++) {
				StackDataType y = yigin2.element[i];
				printf("ADIM: %d ISLEM: %d, YENI DURUM=\n\n", ++adim, y.islem);
				
				for(k = 0; k < 3; k++) {
					for(j = 0; j < 3; j++) {
						printf("%d ", y.tahta[k][j]);
					}
					printf("\n");
				}
				printf("\n");
			}

			return 0;
		}

		
		int t;
		// yukarı
		if(satir > 0) {
			yeni = malloc(sizeof(StackDataType));
			for(i = 0; i < 3; i++) {
				for(j = 0; j < 3; j++) {
					yeni->tahta[i][j] = x.tahta[i][j];
				}
			}

			t = yeni->tahta[satir - 1][sutun];
			yeni->tahta[satir - 1][sutun] = yeni->tahta[satir][sutun];
			yeni->tahta[satir][sutun] = t;

			//satir--;

			yeni->islem = 3;

			add(yigin2, yeni);
		}
		//sol
		if(sutun > 0) {
			yeni = malloc(sizeof(StackDataType));
			for(i = 0; i < 3; i++) {
				for(j = 0; j < 3; j++) {
					yeni->tahta[i][j] = x.tahta[i][j];
				}
			}

			t = yeni->tahta[satir][sutun - 1];
			yeni->tahta[satir][sutun - 1] = yeni->tahta[satir][sutun];
			yeni->tahta[satir][sutun] = t;

			//sutun--;

			yeni->islem = 1;

			add(yigin2, yeni);
		}
		// sag
		if(sutun < 2) {
			yeni = malloc(sizeof(StackDataType));
			for(i = 0; i < 3; i++) {
				for(j = 0; j < 3; j++) {
					yeni->tahta[i][j] = x.tahta[i][j];
				}
			}

			t = yeni->tahta[satir][sutun + 1];
			yeni->tahta[satir][sutun + 1] = yeni->tahta[satir][sutun];
			yeni->tahta[satir][sutun] = t;

			//sutun++;

			yeni->islem = 2;

			add(yigin2, yeni);
		}
		// asagi
		if(satir < 2) {
			yeni = malloc(sizeof(StackDataType));
			for(i = 0; i < 3; i++) {
				for(j = 0; j < 3; j++) {
					yeni->tahta[i][j] = x.tahta[i][j];
				}
			}

			t = yeni->tahta[satir + 1][sutun];
			yeni->tahta[satir + 1][sutun] = yeni->tahta[satir][sutun];
			yeni->tahta[satir][sutun] = t;

			//satir++;

			yeni->islem = 4;

			add(yigin2, yeni);
		}
	}

	printf("Cozum bulunamadi");
	return 0;
}

int compare(StackDataType *x, StackDataType hedef)
{
	int i, j;

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(hedef.tahta[i][j] != x->tahta[i][j]) return 0;
		}
	}

	return 1;
}

int compare2(StackDataType x, StackDataType hedef)
{
	int i, j;

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(hedef.tahta[i][j] != x.tahta[i][j]) return 0;
		}
	}

	return 1;
}

void add(Stack s, StackDataType *e)
{
	int i;
	for(i = 0; i < s.top; i++) {
		if(compare(e, s.element[i])) {
			return;
		}
	}

	push(&yigin1, e);
}

void create(Stack s) {
	s.top = 0;
}

void close(){
}

int push(Stack *s, StackDataType newdata){
	if(s->top < STACKSIZE) {
		int i, j;
		StackDataType new;
		for(i = 0; i < 3; i++) {
			for(j = 0; j < 3; j++) {
				new.tahta[i][j] = newdata.tahta[i][j];
			}
		}
		s->element[s->top++] = new;
		return 1;
	}

	return 0;
}

StackDataType pop(Stack *s){
	if(s->top == 0) {
		printf("Yigin bos!\n");
		exit(1);
	}
	return s->element[--s->top];
}

int isempty(Stack s){
	return (s.top == 0) ? 1 : 0;
}
