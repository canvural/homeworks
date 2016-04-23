#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

int fseekline(FILE *file, int nnumbers, int i, int nprocesses);
void insertion_sort (int *a, int n);
void merge(int a[], int m, int b[], int n, int sorted[]);
void merge_inplace(int arr1[], int m, int arr2[], int n);

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
    int shm_fd;
    int* shared_memory;
    int msize;
    const char *name = "IPCSORT";

    int i, j = 0;

    // Open input file in parent so childeren can access it
    FILE *input = fopen(input_file, "r");
    if(NULL == input) {
        printf("Can't open '%s' for reading!", input_file);
        return 1;
    }

    // Read the firt line
    char firstline[8];
    fgets(firstline, sizeof(firstline), input);

    int nnumbers = atoi(firstline);
    int sorted[nnumbers];
    int csorted = 0;

    msize = nnumbers;

    shm_fd = shm_open(name, O_CREAT | O_EXCL | O_RDWR, S_IRWXU | S_IRWXG);
    if (shm_fd < 0)
    {
        perror("Error in shm_open(): ");
        return 1;
    }

    ftruncate(shm_fd, msize);

    shared_memory = (int *) mmap(NULL, msize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == NULL)
    {
        perror("Error in mmap(): ");
        return 1;
    }

    printf("Shared memory segment allocated correctly (%d bytes).\n", msize);

    for (i = 0; i < nprocesses; i++) {
        if ((pids[i] = fork()) == -1) {
            return 1;
        } else if (pids[i] == 0) {
            int k = fseekline(input, nnumbers, i, nprocesses);

            char *line = malloc(8);

            int a[k];

            for(j = 0; j < k; j++) {
                fgets(line, sizeof(line), input);
                a[j] = atoi(line);
            }

            insertion_sort(a, k);

            int n = (nnumbers / nprocesses) * i;

            for(j = 0; j < k; j++, n++) {
                shared_memory[n] = a[j];
            }

            exit(0);
        } else {
            wait(NULL);
        }
    }

    insertion_sort(shared_memory, nnumbers);

    FILE *out = fopen(output_file, "w");

    fprintf(out, "%d\n", nnumbers);

    for(j = 0; j < nnumbers; j++) {
        fprintf(out, "%d\n", shared_memory[j]);
    }

    shm_unlink(name);

    fclose(input);
    fclose(out);

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
