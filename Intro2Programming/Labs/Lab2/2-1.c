#include <stdio.h>

int main() {

	int c;
	int digits = 0;
	int letters = 0;
	printf("Type c\n");
	while ((c=getchar()) != EOF) {
		if(c == '\n') continue;
		printf("Your char is : %c \n", c);
		if (isdigit(c)) {
			digits++;
		}
		else
			letters++;
	}

	printf("The number of digits is...");
	printf("%d\n",digits);
	printf("and the number of letters is...");
	printf("%d\n", letters);

	return 0;
}

