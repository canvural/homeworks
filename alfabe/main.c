#include <stdio.h>
#include <string.h>

int main()
{
	FILE *f;
	char alfabe[256];
	int i, k, alfabe_s;
	
	f = fopen("alfabe.txt", "r");
	if(NULL == f) {
		printf("Dosya açılamadı!");
		return 1;
	}
	
	if(fgets(alfabe, sizeof(alfabe), f) == NULL) {
		printf("Dosyadan okunamadı");
		return 1;
	}
	
	alfabe_s = strlen(alfabe);
	
	fclose(f);
	
	
	for(i = 0; i < alfabe_s; i++) {
		if(i % 8 == 0) {
			printf("\n");
		}
		
		printf("%c", alfabe[i]);
	}
	
	printf("\n\n");
	
	for(i = alfabe_s - 1, k = 0; i >= 0; i--, k++) {
		if(k % 4 == 0) {
			printf(" ");
		}
		
		if(k % 8 == 0) {
			printf("\n");
		}
		
		printf("%c", alfabe[i]);
	}
	
	return 0;
}
