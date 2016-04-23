#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "main.h"

void search_for_word(FILE *file, char *word)
{
	// Current line number
	int line_n = 0;

	// How many times the word found in the current line
	int times = 0;

	// Current line
	char *line;

	// Mark line
	char *mark;

	// Length of word
	size_t len = strlen(word);

	// Determine where shuld we write
	FILE *f = foutput ? output_f : stdout;

	// Read file line by line and progress
	while((line = read_line(file)) != NULL) {
		line_n++;

		char const *p = line;
	    for (times = 0; ; ++times) {
	        p = strstr(p, word);
	        if (!p)
	            break;

	        p+=len;
	    }
		
		// Print if we found the word in line
		if(times) {
			fprintf(f, "\nL%d/%d: %s\n", line_n, times, line);
			fprintf(f, "      ");

			p = line;
			
			int prev = 0;
		    for (;;) {
		        p = strstr(p, word);
		        if (!p)
		            break;
		        int a = (p - line) - prev;
		        
		        int i;
		        for(i = 0; i < a; i++) {
		        	fprintf(f, "%c", ' ');
		        }
		        
		        for(i = 0; i < len; i++)
		        	fprintf(f, "%c", '^');

		        prev = a + len;
		        p += len;
			}
		}
	}
}

void replace_word(FILE *file, char *search, char *replace)
{
	char *line;

	// Determine where shuld we write
	FILE *f = foutput ? output_f : stdout;

	// Read file line by line and progress
	while((line = read_line(file)) != NULL) {
		search_replace(line, search, replace);
		fprintf(f, "%s\n", line);
	}
}

char *read_line(FILE *file) 
{ 
	if(fgets(lineG, sizeof(lineG), file) != NULL) {
		// Clean the new line character if there is one
		size_t ln = strlen(lineG) - 1;
		if (lineG[ln] == '\n')
		    lineG[ln] = '\0';

		return lineG;
	}
		
	return NULL; 
}

void search_replace(char * o_string, char * s_string, char * r_string) {
    //a buffer variable to do all replace things
    char buffer[4096];
    //to store the pointer returned from strstr
    char * ch;
 
    //first exit condition
    if(!(ch = strstr(o_string, s_string)))
 		return;
 
    //copy all the content to buffer before the first occurrence of the search string
    strncpy(buffer, o_string, ch-o_string);
 
    //prepare the buffer for appending by adding a null to the end of it
    buffer[ch-o_string] = 0;
 
    //append using sprintf function
    sprintf(buffer+(ch - o_string), "%s%s", r_string, ch + strlen(s_string));
 
    //empty o_string for copying
    o_string[0] = 0;
    strcpy(o_string, buffer);
    //pass recursively to replace other occurrences
    return search_replace(o_string, s_string, r_string);
 }