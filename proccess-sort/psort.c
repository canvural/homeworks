#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int fseekline(FILE *file, int nnumbers, int i, int nprocesses);
void insertion_sort (int *a, int n);
void merge(int a[], int m, int b[], int n, int sorted[]);

int main(int argc, char **argv)
{
    int nprocesses = 0;
    char *input_file  = NULL;
    char *output_file = NULL;

    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "p:i:o:")) != -1) {
        switch (c) {
            case 'p':
            nprocesses = atoi(optarg);
            break;
            case 'i':
            input_file = optarg;
            break;
            case 'o':
            output_file = optarg;
            break;
            case '?':
            printf("Usage: ./psort -p [Number] -i [Input file] -o [Output file]");
            return 1;
            default:
            printf("Usage: ./psort -p [Number] -i [Input file] -o [Output file]");
            return 1;
        }
    }

    if(!nprocesses) {
        printf("Please pass number of processes to spawn as an argument!");
        return 1;
    }

    if(input_file == NULL) {
        printf("Please give an input file!");
        return 1;
    }

    if(output_file == NULL) {
        printf("Please give an output file!");
        return 1;
    }

    // Array of process ids
    pid_t pids[nprocesses];

    int i, j;

    // Open input file in parent so childeren can access it
    FILE *input = fopen(input_file, "r");
    if(NULL == input) {
        printf("Can't open '%s' for reading!", input_file);
        perror("");
        return 1;
    }

    /***************
    *** STAGE 1 ***
    ***************/
    // Read the firt line
    char firstline[8];
    fgets(firstline, sizeof(firstline), input);

    int nnumbers = atoi(firstline);

    for (i = 0; i < nprocesses; i++) {
        if ((pids[i] = fork()) == -1) {
            return 1;
        } else if (pids[i] == 0) {
            int k = fseekline(input, nnumbers, i, nprocesses);

            // Create a buffer to hold "i.txt"
            char *buf = malloc(8);
            char *line = malloc(8);
            sprintf(buf, "%d.txt", i + 1);

            FILE *out = fopen(buf, "w");
            if(NULL == out) {
                exit(1);
            }

            for(j = 0; j < k; j++) {
                fgets(line, sizeof(line), input);
                fprintf(out, "%s", line);
            }

            fclose(out);

            printf("PID: %d created %s\n", getpid(), buf);
            free(buf);
            exit(0);
        } else{
            wait(NULL);
        }
    }

    fclose(input);

    /*********************
    *** STAGE 1 ENDED ***
    *********************/

    /***************
    *** STAGE 2 ***
    ***************/

    int sorted_pids[nprocesses];

    for (i = 0; i < nprocesses; i++) {
        if ((pids[i] = fork()) == -1) {
            return 1;
        }

        if (pids[i] == 0) {
            char buf[16];
            sprintf(buf, "%d.txt", i + 1);
            FILE *f = fopen(buf, "r");

            int k = nnumbers / nprocesses;

            // Array to hold numbers in file
            int a[k];
            int l = 0;

            while(!feof(f)) {
                fscanf(f, "%d", &a[l]);
                l++;
            }

            fclose(f);

            // Sort the numbers
            insertion_sort(a, k);

            // Write them to files
            sprintf(buf, "%d.txt", getpid());
            FILE *fpid = fopen(buf, "w");

            for (l = 0; l < k; l++) {
                fprintf(fpid, "%d\n", a[l]);
            }

            printf("PID %d sorted numbers into %s\n", getpid(), buf);

            fclose(fpid);

            exit(0);
        }

    }

    pid_t pid;
    j = nprocesses;
    i = 0;
    while (j > 0) {
        pid = wait(NULL);
        // Save the pid for stage 3
        sorted_pids[i] = pid;
        i++;
        --j;
    }

    /*********************
    *** STAGE 2 ENDED ***
    *********************/


    /***************
    *** STAGE 3 ***
    ***************/

    int h = nprocesses / 2;
    int n = 0;
    int k = nnumbers / nprocesses;
    while(h >= 1) {
        for (i = 0; i < h; i++, n = n + 2) {
            if ((pids[i] = fork()) == -1) {
                return 1;
            }

            if (pids[i] == 0) {
                char buf[16], buf2[16], buf3[16];
                sprintf(buf, "%d.txt", getpid());
                sprintf(buf2, "%d.txt", sorted_pids[n]);
                sprintf(buf3, "%d.txt", sorted_pids[n + 1]);

                FILE *f  = fopen(buf2, "r");
                FILE *f2 = fopen(buf3, "r");

                // Array to hold numbers in file
                int a[k], a2[k];
                int l = 0;

                while(!feof(f)) {
                    fscanf(f, "%d", &a[l]);
                    fscanf(f2, "%d", &a2[l]);
                    l++;
                }

                fclose(f);
                fclose(f2);

                int sorted[k*2];

                merge(a, k, a2, k, sorted);

                FILE *f3 = fopen(buf, "w");

                for (l = 0; l < k*2; l++) {
                    fprintf(f3, "%d\n", sorted[l]);
                }

                fclose(f3);

                printf("STAGE 3: PID %d opens %d.txt and %d\n", getpid(), sorted_pids[n], sorted_pids[n + 1]);
                exit(0);
            }
        }

        j = h;
        i = 0;
        while (j > 0) {
            pid = wait(NULL);
            sorted_pids[i] = pid;
            i++;
            --j;
        }

        h = h / 2;
        n = 0;
        k = k*2;
    }

    // Create the output file
    FILE *output = fopen(output_file, "w");
    fprintf(output, "%s", firstline);
    char buf[16];
    sprintf(buf, "%d.txt", sorted_pids[0]);
    FILE *final  = fopen(buf, "r");
    if(NULL == final) {
        printf("Can't open %s", buf);
        return 1;
    }

    while(!feof(final)) {
        int z;
        fscanf(final, "%d", &z);
        fprintf(output, "%d\n", z);
    }

    fclose(final);
    fclose(output);

    return 0;
}

/*
* A function to skip lines with counting newlines.
*/
int fseekline(FILE *file, int nnumbers, int i, int nprocesses)
{
    int k = nnumbers / nprocesses;
    int j = i * k;
    int l = 0;

    // Shortcut
    if(j == 0) {
        return k;
    }

    do {
        char c = fgetc(file);
        if(c == EOF) {
            rewind(file);
            l = -1;
        }

        if(c == '\n') {
            l++;
        }
    } while(l < j);

    return k;
}

// Insertion sort algorithm
// See: http://rosettacode.org/wiki/Sorting_algorithms/Insertion_sort#C
void insertion_sort (int *a, int n) {
    int i, j, t;
    for (i = 1; i < n; i++) {
        t = a[i];
        for (j = i; j > 0 && t < a[j - 1]; j--) {
            a[j] = a[j - 1];
        }
        a[j] = t;
    }
}

// See: http://www.programmingsimplified.com/c/source-code/c-program-merge-two-arrays
void merge(int a[], int m, int b[], int n, int sorted[]) {
    int i, j, k;

    j = k = 0;

    for (i = 0; i < m + n;) {
        if (j < m && k < n) {
            if (a[j] < b[k]) {
                sorted[i] = a[j];
                j++;
            }
            else {
                sorted[i] = b[k];
                k++;
            }
            i++;
        }
        else if (j == m) {
            for (; i < m + n;) {
                sorted[i] = b[k];
                k++;
                i++;
            }
        }
        else {
            for (; i < m + n;) {
                sorted[i] = a[j];
                j++;
                i++;
            }
        }
    }
}
