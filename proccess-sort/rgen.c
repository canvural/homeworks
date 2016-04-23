#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

unsigned int randr(int min, int max);

int main(int argc, char **argv)
{
    srand(time(NULL));

    int number_of_nums;
    int low_limit;
    int high_limit;
    char *output_file = NULL;

    int c;

    opterr = 0;
    while ((c = getopt (argc, argv, "n:l:h:o:")) != -1) {
        switch (c) {
            case 'n':
                number_of_nums = atoi(optarg);
                break;
            case 'l':
                low_limit = atoi(optarg);
                break;
            case 'h':
                high_limit = atoi(optarg);
                break;
            case 'o':
                output_file = optarg;
                break;
            case '?':
                printf("Usage: ./rgen -n [Number] -l [Low limit] -h [High limit] -o [Output file]");
                return 1;
            default:
                printf("Usage: ./rgen -n [Number] -l [Low limit] -h [High limit] -o [Output file]");
                return 1;
        }
    }

    long long int random_number_size = pow(2, number_of_nums);

    FILE *output = fopen(output_file, "w");
    if(NULL == output) {
        printf("Can't open '%s' for writing!", output_file);
        return 1;
    }

    // Write the total number of numbers
    fprintf(output, "%lld\n", random_number_size);

    int i;

    for(i = 0; i < random_number_size; i++) {
        fprintf(output, "%d\n", randr(low_limit, high_limit));
    }

    fclose(output);

    return 0;
}

// Function to generate random number between range
unsigned int randr(int min, int max)
{
       double scaled = (double)rand()/RAND_MAX;

       return (max - min +1)*scaled + min;
}
