#include <stdio.h>
#include <math.h>

double ortalama(int array[], int size)
{
    int i;
    double toplam = 0;

    for(i = 0; i < size; i ++) {
        toplam += array[i];
    }

    return toplam / size;
}

double standart(int array[], int size)
{
    double ort = ortalama(array, size);
    double temp = 0;

    int i;

    for(i = 0; i < size; i++){
        temp += (array[i] - ort) * (array[i] - ort);
    }

    return sqrt(temp / size);
}

int main()
{
	srand(time(NULL));
    int size = 0;

    printf("Kaç sayı gireceksiniz: ");
    scanf("%d", &size);

    int array[size];
    int i;
    
    for(i = 0; i < size; i++){
        array[i] = i + 1;;
    }

    int choice;

    printf("Yapacağınız işlemi girin: ");
    scanf("%d", &choice);

    if(choice == 1) {
        double ort = ortalama(array, size);
        double std = standart(array, size);
		
		for(i = 0; i < size; i++) {
            printf("%f ", (i - ort) / std);
        }
    } else if(choice == 2) {
		double std = standart(array, size);
		
		for(i = 0; i < size; i++) {
            printf("%f ", i / std);
        }
	} else if(choice == 3) {
		for(i = 0; i < size; i++) {
            printf("%d ", (i - array[rand() % size]) / array[rand() % size]);
        }
	}

    return 0;
}
