#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char buf[256];
    unsigned long int i,
        number_of_letters,
        number_of_digits,
        len;

    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        number_of_letters = 0;
        number_of_digits = 0;
        len = strlen(buf);

        for(i = 0; i < len; i++) {
            if(isalpha(buf[i])) {
                number_of_letters++;
            } else if(isdigit(buf[i])) {
                number_of_digits++;
            }
        }

        printf("There are %d letters and %d digits in %s\n",
            number_of_letters, number_of_digits, buf
        );
    }

    return 0;
}
