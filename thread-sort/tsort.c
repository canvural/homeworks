#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

unsigned int randr(int min, int max);
void *random_thread_function(void *arg);
void *sort_thread_function(void *arg);
void *merge_thread_function(void *arg);
int compare (const void * a, const void * b);

int number_of_nums;
int number_of_threads;
int n_thread_sort;
long long int random_number_size;
int low_limit;
int high_limit;
pthread_mutex_t random_array_mutex = PTHREAD_MUTEX_INITIALIZER;
int *random_array = NULL;

int main(int argc, char **argv)
{
    srand(time(NULL));

    char *sorted_file = NULL;
    char *output_file = NULL;

    int c;

    opterr = 0;
    while ((c = getopt (argc, argv, "r:m:l:h:n:s:o:")) != -1) {
        switch (c) {
            case 'r':
                number_of_threads = atoi(optarg);
                break;
            case 'm':
                number_of_nums = atoi(optarg);
                break;
            case 'l':
                low_limit = atoi(optarg);
                break;
            case 'h':
                high_limit = atoi(optarg);
                break;
            case 'n':
                sorted_file = optarg;
                break;
            case 's':
                n_thread_sort = atoi(optarg);
                break;
            case 'o':
                output_file = optarg;
                break;
            case '?':
                printf("Usage: ./tsort -r 2 -m 6 -l 30 -h 50 -n numbers.txt -s 4 -o sorted.txt");
                return 1;
            default:
                printf("Usage: ./tsort -r 2 -m 6 -l 30 -h 50 -n numbers.txt -s 4 -o sorted.txt");
                return 1;
        }
    }

    random_number_size = pow(2, number_of_nums);

    FILE *output = fopen(output_file, "w");
    if(NULL == output) {
        printf("Can't open '%s' for writing!", output_file);
        return 1;
    }

    FILE *sorted = fopen(sorted_file, "w");
    if(NULL == sorted) {
        printf("Can't open '%s' for writing!", sorted_file);
        return 1;
    }

    random_array = malloc(random_number_size * sizeof(int));
    if(NULL == random_array) {
        printf("Cannot allocate memory!");
        return 1;
    }

    pthread_t *threads = malloc(number_of_threads * sizeof(pthread_t));
    if(NULL == threads) {
        printf("Cannot allocate memory!");
        return 1;
    }

    pthread_t *sort_threads = malloc(n_thread_sort * sizeof(pthread_t));
    if(NULL == sort_threads) {
        printf("Cannot allocate memory!");
        return 1;
    }

    long i;

    for(i = 0; i < number_of_threads; i++) {
        pthread_create(&threads[i], NULL, random_thread_function, (void *) i);
    }

    for(i = 0; i < number_of_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    for(i = 0; i < random_number_size; i++) {
        fprintf(sorted, "%d\n", random_array[i]);
    }

    for(i = 0; i < n_thread_sort; i++) {
        pthread_create(&sort_threads[i], NULL, sort_thread_function, (void *) i);
    }

    for(i = 0; i < n_thread_sort; i++) {
        pthread_join(sort_threads[i], NULL);
    }

    int k = (random_number_size / n_thread_sort) / 2;
    int n = 0;
    int m = (random_number_size / n_thread_sort);

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
            pthread_create(&merge_threads[i], NULL, merge_thread_function, (void *) arr);
        }

        int t;
        for(t = 0; t < k; ++t) {
            pthread_join(merge_threads[t], NULL);
        }

        k = k / 2;
        n = 0;
        m = m*2;
    }

    for(i = 0; i < random_number_size; i++) {
        fprintf(output, "%d\n", random_array[i]);
    }

    return 0;
}

// Function which each thread will run
void *random_thread_function(void *arg)
{
    long j = (long) arg;
    int k = (random_number_size / number_of_threads);
    int h = (k * (j + 1)) - 1;
    int l = (h - k) + 1;

    int i;

    for(i = l; i <= h; i ++) {
        pthread_mutex_lock(&random_array_mutex);
        random_array[i] = randr(low_limit, high_limit);
        pthread_mutex_unlock(&random_array_mutex);
    }
}

// Function which each thread will run
void *sort_thread_function(void *arg)
{
    long j = (long) arg;
    int k = (random_number_size / n_thread_sort);
    int h = (k * (j + 1)) - 1;
    int l = (h - k) + 1;
    int i, g;

    int *part = malloc(k + 1 * sizeof(int));

    for(i = l, g = 0; i <= h; i++, g++) {
        part[g] = random_array[i];
    }

    qsort (part, g, sizeof(int), compare);

    for(i = l, g = 0; i <= h; i++, g++) {
        pthread_mutex_lock(&random_array_mutex);
        random_array[i] = part[g];
        pthread_mutex_unlock(&random_array_mutex);
    }
}

void *merge_thread_function(void *arg)
{
    int (*j)[2] = (int(*)[2]) arg;
    int k = (random_number_size / n_thread_sort);
    int h = ((*j)[0] * ((*j)[1] + 1)) - 1;
    int l = (h - (*j)[0]) + 1;

    pthread_mutex_lock(&random_array_mutex);
    qsort(random_array, random_number_size, sizeof(int), compare);
    pthread_mutex_unlock(&random_array_mutex);
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
