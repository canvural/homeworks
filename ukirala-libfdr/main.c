#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
#include "libfdr/fields.h"

int main(int argc, char **argv)
{
    char *input_file  = NULL;
    char *output_file = NULL;

    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "i:o:")) != -1) {
        switch (c) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case '?':
            default:
                printf("Usage: %s -i [Input file] -o [Output file]", argv[0]);
                return 1;
        }
    }

    if(input_file == NULL) {
        printf("No input file given. Using the default one\n");
        input_file = "default.dat";
    }

    if(output_file == NULL) {
        printf("No output file given. Using 'output.dat' as default\n");
        output_file = "output.dat";
    }

    // Open the input file using libfdr
    IS is;
    is = new_inputstruct(input_file);
    if (is == NULL) {
        perror("Error opening input file");
        return 1;
    }

    int i;

    // The ouput buffer. Assuming the output will not be longer than 1024 chars
    char *buffer = malloc(1025);
    if(NULL == buffer) {
        perror("Malloc failed");
        return 1;
    }

    while(get_line(is) >= 0) {
        // Decide which command to run
        if(strcmp(is->fields[0], "yaz:") == 0) {
            yaz(buffer, is->fields, is->NF - 1);
        } else if(strcmp(is->fields[0], "sil:") == 0) {
            sil(buffer, is->fields, is->NF - 1);
        } else if(strcmp(is->fields[0], "sonagit:") == 0) {
            // Nothing to do
        } else if(strcmp(is->fields[0], "dur:") == 0) {
            break;
        } else {
            // Unknown command, just ignore
        }
    }

    FILE *out = fopen(output_file, "w");
    if(NULL == out) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(out, "%s", buffer);

    fclose(out);

    printf("'%s' created", output_file);

    jettison_inputstruct(is);

    return 0;
}

static inline void remove_char_at_index(char *str, int index)
{
    memmove(str + index, str + (index + 1), strlen(str) - index);
}

void remove_char(char *str, char garbage, int count)
{
    // Counter of how many chars we deleted
    int counter = 0;

    while(1) {
        // Break if we deleted enough
        if(counter == count) {
            break;
        }

        char *pos = strrchr(str, garbage);
        if(NULL == pos) {
            // There is no more char to delete
            break;
        }

        remove_char_at_index(str, pos - str);

        counter++;
    }
}

void yaz(char *buf, char *fields[], int nf)
{
    // Skip the command
    fields++;

    int i;

    for(i = 0; i < nf; i+=2) {
        if(!is_number(fields[i])) {
            printf("Unrecognized format: '%s %s' It should be in '(integer) (character)' format!", fields[i], fields[i + 1]);
            exit(EXIT_FAILURE);
        }

        int j = atoi(fields[i]), k;

        for(k = 0; k < j; k++) {
            if(strcmp(fields[i+1], "\\b") == 0) {
                strcat(buf, " ");
            } else if(strcmp(fields[i+1], "\\n") == 0) {
                strcat(buf, "\n");
            } else {
                strcat(buf, fields[i+1]);
            }
        }
    }
}

void sil(char *buf, char *fields[], int nf)
{
    // Skip the command
    fields++;

    int i;

    for(i = 0; i < nf; i+=2) {
        if(!is_number(fields[i])) {
            printf("Unrecognized format: '%s %s' It should be in '(integer) (character)' format!", fields[i], fields[i + 1]);
            exit(EXIT_FAILURE);
        }
        remove_char(buf, *(fields[i+1]), atoi(fields[i]));
    }
}

int is_number (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}
