#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>

#include "worldutils.h"

int min_number = 0;

int word_in_string (const char *str, const char * wd, int flag_case, int flag_exact)
{
    int ret = 0,
        str_len = strlen(wd);
    char *p;

    p = my_strstr(p, wd, flag_case);

    if(!p) {
        return 0;
    }

    if(flag_exact) {
        while ((p = my_strstr(p, wd, flag_case)) != NULL) {
            char *q = p + str_len;

            if (p == str || isblank(*(p - 1))) {
                if (*q == '\0' || isblank(*q)) {
                    return 1;
                }
            }

            p = q;
        }

        return 0;
    }

    return 1;
}

int words_in_string (const char *str, char * wds[], int size, int flag_case, int flag_exact)
{
    int i,
        word_count = 0;

    for(i = 0; i < size; i++) {
        if(word_in_string(str, wds[i], flag_case, flag_exact)) {
            word_count++;
        }
    }

    return word_count;
}

void set_min_number(int number)
{
    if(number < 0) {
        number = 0;
    }

    min_number = number;
}

int is_matching(const char * str, char * wds[], int size, int flag_case, int flag_exact)
{
    if(words_in_string(str, wds, size, flag_case, flag_exact) >= min_number) {
        return 1;
    }

    return 0;
}

char *my_strstr(const char *s1, const char*s2, int flag_case)
{
    char *p;

    if(flag_case) {
        p = strcasestr(s1, s2);
    } else {
        p = strstr(s1, s2);
    }

    return p;
}
