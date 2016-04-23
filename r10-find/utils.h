#ifndef UTILS_H_
#define UTILS_H_

// Buffer
char lineG [255];

// Searchs a file for a word and prints occurences marked
void search_for_word(FILE *file, char *word);

// Replace word with specified word
void replace_word(FILE *file, char *search, char *replace);

// Reads one line of a file and return it
char *read_line(FILE *file);

void search_replace(char * o_string, char * s_string, char * r_string);

#endif // UTILS_H_