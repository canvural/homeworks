#include <stdio.h>

int main()
{
    char *first_name = "Can",
         *last_name  = "Vural";

    int i;

    for(i = 0; i < 10; i++) {
        printf("%s", first_name);
        if(i != 9) {
            printf(";");
        } else {
            printf(".\n");
        }
    }

    for(i = 0; i < 5; i++) {
        printf("%s\n", last_name);
    }

    return 0;
}
