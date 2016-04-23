#ifndef WORLD_UTILS_H
#define WORLD_UTILS_H

extern int min_number;

int word_in_string (const char *str, const char * wd, int flag_case, int flag_exact);
int words_in_string (const char *str, char * wds[], int size, int flag_case, int flag_exact);
void set_min_number(int number);
int is_matching(const char * str, char * wds[], int size, int flag_case, int flag_exact);
char *my_strstr(const char *s1, const char*s2, int flag_case);

#endif
