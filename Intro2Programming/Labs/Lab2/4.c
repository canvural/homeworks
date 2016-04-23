#include <stdio.h>
#include <string.h>

int main()
{
    char buf[256];
    int i,
        len;

    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        len = strlen(buf) - 1; // -1 because newline

        if(len % 2 != 0) {
            printf("> %s", buf);
        }
    }

    return 0;
}
