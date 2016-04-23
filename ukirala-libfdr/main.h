#ifndef MAIN_H
#define MAIN_H

// Removes one char at the "index" from "str"
static inline void remove_char_at_index(char *str, int index);

// Starting from end, 'count' times, removes 'garbage' from 'str'
void remove_char(char *str, char garbage, int count);

void yaz(char *buf, char *fields[], int nf);
void sil(char *buf, char *fields[], int nf);
int is_number (const char * s);

#endif
