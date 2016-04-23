#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void *randomfunc(void *arg);
void *sortfunc(void *arg);
void *mergefunc(void *arg);
int compare (const void * a, const void * b);
void *mergefunc(void *arg);
unsigned int randr(int min, int max);

int non;
int not;
int nts;
int rns;
int llim;
int hlim;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int *random_array = NULL;

int main(int argc, char **argv)
{
    srand(time(NULL));

    int c;

    char *sf = NULL;
    char *of = NULL;

    opterr = 0;
    while ((c = getopt (argc, argv, "r:m:l:h:n:s:o:")) != -1) {
        switch (c) {
            case 'r':
                not = atoi(optarg);
                break;
            case 'm':
                non = atoi(optarg);
                break;
            case 'l':
                llim = atoi(optarg);
                break;
            case 'h':
                hlim = atoi(optarg);
                break;
            case 'n':
                sf = optarg;
                break;
            case 's':
                nts = atoi(optarg);
                break;
            case 'o':
                of = optarg;
                break;
            case '?':
                printf("Usage: ./tsort -r 2 -m 6 -l 30 -h 50 -n numbers.txt -s 4 -o sorted.txt");
                return 1;
            default:
                printf("Usage: ./tsort -r 2 -m 6 -l 30 -h 50 -n numbers.txt -s 4 -o sorted.txt");
                return 1;
        }
    }

    rns = pow(2, non);
    FILE *output = fopen(of, "w");
    FILE *sorted = fopen(sf, "w");
    random_array = malloc(rns * sizeof(int));
    pthread_t *threads = malloc(not * sizeof(pthread_t));
    pthread_t *sort_threads = malloc(nts * sizeof(pthread_t));

    long i;

    for(i = 0; i < not; i++) {
        pthread_create(&threads[i], NULL, randomfunc, (void *) i);
        pthread_join(threads[i], NULL);
    }

    for(i = 0; i < rns; i++) {
        fprintf(sorted, "%d\n", random_array[i]);
    }

    for(i = 0; i < nts; i++) {
        pthread_create(&sort_threads[i], NULL, sortfunc, (void *) i);
    }

    for(i = 0; i < nts; i++) {
        pthread_join(sort_threads[i], NULL);
    }

    int k = (rns / nts) / 2;
    int n = 0;
    int m = (rns / nts);

    pthread_t *merge_threads = malloc(k * sizeof(pthread_t));
    if(NULL == merge_threads) {
        printf("Cannot allocate memory!");
        return 1;
    }

    while(k >= 1) {
        for(i = 0; i < k; i++, n = n + 2) {
            int *arr = malloc(2 * sizeof(int));

            arr[0] = k;
            arr[1] = i;
            pthread_create(&merge_threads[i], NULL, mergefunc, (void *) arr);
        }

        int t;
        for(t = 0; t < k; ++t) {
            pthread_join(merge_threads[t], NULL);
        }

        k = k / 2;
        n = 0;
        m = m*2;
    }

    for(i = 0; i < rns; i++) {
        fprintf(output, "%d\n", random_array[i]);
    }

    return 0;
}

// Function which each thread will run
void *randomfunc(void *arg)
{
    long j = (long) arg;
    int k = (rns / not);
    int h = (k * (j + 1)) - 1;
    int l = (h - k) + 1;

    int i;

    for(i = l; i <= h; i ++) {
        pthread_mutex_lock(&mutex);
        random_array[i] = randr(llim, hlim);
        pthread_mutex_unlock(&mutex);
    }
}

// Function which each thread will run
void *sortfunc(void *arg)
{
    long j = (long) arg;
    int k = (rns / nts);
    int h = (k * (j + 1)) - 1;
    int l = (h - k) + 1;
    int i, g;

    int *part = malloc(k + 1 * sizeof(int));

    for(i = l, g = 0; i <= h; i++, g++) {
        part[g] = random_array[i];
    }

    qsort (part, g, sizeof(int), compare);

    for(i = l, g = 0; i <= h; i++, g++) {
        pthread_mutex_lock(&mutex);
        random_array[i] = part[g];
        pthread_mutex_unlock(&mutex);
    }
}

void *mergefunc(void *arg)
{
    int (*j)[2] = (int(*)[2]) arg;
    int k = (rns / nts);
    int h = ((*j)[0] * ((*j)[1] + 1)) - 1;
    int l = (h - (*j)[0]) + 1;

    pthread_mutex_lock(&mutex);
    qsort(random_array, rns, sizeof(int), compare);
    pthread_mutex_unlock(&mutex);
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

// Function to generate random number between range
unsigned int randr(int min, int max)
{
    double scaled = (double)rand()/RAND_MAX;

    return (max - min +1)*scaled + min;
}
