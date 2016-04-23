#include <stdio.h>
#include <string.h>

int main()
{
    char word[256];

    while(fgets(word, sizeof(word), stdin) != NULL) {

        int len = strlen(word);

        if(word[0] == word[len - 2]) {
            printf("> %s", word);
        }
    }

    return 0;
}
