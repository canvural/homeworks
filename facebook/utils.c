#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char *read_line(FILE *file)
{
	if (file == NULL) {
        fprintf(stderr, "Can't open file!");
        return NULL;
    }

    // Allocate 255 byte for one line. +1 for NULL terminator.
    char *line = malloc(256);
    if (line == NULL) {
        fprintf(stderr, "Can not allocate memory for line buffer!");
        return NULL;
    }

    if(fgets(line, 256, file) != NULL) {
    	size_t ln = strlen(line) - 1;
		if (line[ln] == '\n')
		    line[ln] = '\0';
		if (line[ln - 1] == '\r')
		    line[ln - 1] = '\0';
    	return line;
    }

    // There should be an error if we are here so
    // free the allocated space and return NULL
    free(line);
    return NULL;
}