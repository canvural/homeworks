/**
 * Some helper functions.
 */

#ifndef UTILS_H_
#define UTILS_H_

// Reads a line or 255 byte from a file and trims newline characters.
char *read_line(FILE *file);

// Checks if two string is anagram of each other.
int check_anagram(const char * str1, const char * str2);

char *read_words();

#endif
