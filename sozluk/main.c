#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *read_line(FILE *file)
{
	if (file == NULL) {
        fprintf(stderr, "Can't open file!");
        return NULL;
    }

    // Allocate 255 byte for one line. +1 for NULL terminator.
    char *line = malloc(256);
    if (line == NULL) {
        fprintf(stderr, "Can not allocate memory for line buffer!");
        return NULL;
    }

    if(fgets(line, 256, file) != NULL) {
    	size_t ln = strlen(line) - 1;
		if (line[ln] == '\n')
		    line[ln] = '\0';
		if (line[ln - 1] == '\r')
		    line[ln - 1] = '\0';
    	return line;
    }

    // There should be an error if we are here so
    // free the allocated space and return NULL
    free(line);
    return NULL;
}

int main()
{
	// önceden oluşturulan dosya varsa onları siliyoruz
	remove("turkce.txt");
	remove("ingilizce.txt");

	FILE *sozluk = fopen("sozluk.txt", "r");
	if(NULL == sozluk) {
		fprintf(stderr, "Can't open 'sozluk.txt' file for reading. Please make sure it exists!\n");
		return 1;
	}

	char *line;
	char turkish[256];
	char english[256];

	// Toplam 200 kelime olacağını biliğimiz için dinamik dizi oluşturmaya gerek yok
	char turkish_words[100][256];
	char english_words[100][256];

	// sozluk.txt dosyasından kelimeleri okuyup türkçe ve ingilizce olarak ayrı dizilere atıyoruz
	int i = 0;
	while((line = read_line(sozluk)) != NULL) {
		sscanf(line, "%255[^ ] %255[^\n]", turkish, english);
		
		strcpy(turkish_words[i], turkish);
		strcpy(english_words[i], english);

		i++;

		free(line);
	}

	int j = 0;
	char temp[256], temp2[256];

	// Çok basit bir sıralama algoritması
	for (i = 0; i < 20 ; i++) {
    	for (j = i + 1; j < 20; j++) {
            if (strcmp(turkish_words[i], turkish_words[j]) > 0) {
                strcpy(temp, turkish_words[i]);
                strcpy(temp2, english_words[i]);
                strcpy(turkish_words[i], turkish_words[j]);
                strcpy(english_words[i], english_words[j]);
                strcpy(turkish_words[j], temp);
                strcpy(english_words[j], temp2);
            }
        }
    }

    FILE *turkish_f = fopen("turkce.txt", "w");
    if(NULL == turkish_f) {
    	fprintf(stderr, "Can't open 'turkce.txt' for writing!\n");
		return 1;
    }

    FILE *english_f = fopen("ingilizce.txt", "w");
    if(NULL == english_f) {
    	fprintf(stderr, "Can't open 'ingilizce.txt' for writing!\n");
		return 1;
    }

    // Sıralanmış kelimeleri dosyaya yazıyoruz
    for (i = 0; i < 20 ; i++) {
    	fprintf(turkish_f, "%s\n", turkish_words[i]);
    	fprintf(english_f, "%s\n", english_words[i]);
    }

    // Programın ikinci bölümü.
    // Verilen kelimeyi dosyalarda arama

    char aranacak[256];
    printf("Arama yapmak istediğiniz kelimeyi girin: ");
    scanf("%255s", aranacak);

    int found = 0;
    for(i = 0; i < 20; i++) {
    	if(strcmp(turkish_words[i], aranacak) == 0) {
    		printf("%s kelimesi turkce.txt dosyasında %d. sıradadır.\n", aranacak, i + 1);
    		printf("%s kelimesinin İngilizce karşılığı %s kelimesidir.", aranacak, english_words[i]);
    		found = 1;
    		break;
    	}
    }

    if(!found) {
    	for(i = 0; i < 20; i++) {
	    	if(strcmp(english_words[i], aranacak) == 0) {
	    		printf("%s kelimesi ingilizce.txt dosyasında %d. sıradadır.\n", aranacak, i + 1);
	    		printf("%s kelimesinin Türkçe karşılığı %s kelimesidir.", aranacak, turkish_words[i]);
	    		
	    		break;
	    	}
    	}
    }

    fclose(sozluk);
    fclose(turkish_f);
    fclose(english_f);
	
	return 0;
}