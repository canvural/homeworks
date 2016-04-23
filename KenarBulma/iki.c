#include <stdio.h>
#include <stdlib.h>

#include "image.h"

int compare(const void* a, const void* b)
{
    int int_a = * ((int*) a);
    int int_b = * ((int*) b);

    if ( int_a == int_b  ) return 0;
    else if ( int_a < int_b  ) return -1;
    else return 1;
}

int main()
{
    char **im = image();
    char kernel[3][3] = {
        {'0', '1', '0'},
        {'1', '1', '1'},
        {'0', '1', '0'}
    };

    int i, j, k, l;
	
	// Allocate memory for the output image
	char **out = malloc(101 * sizeof(char *));
	for(i = 0; i < 101; i++)
    	out[i] = malloc(120 * sizeof(char));
    
    // Print the image
    for(i = 0; i < 100; i++) {
        for(j = 0; j < 120; j++) {
            printf("%c", im[i][j] == '0' ? ' ' : '#');
        }
        printf("\n");
    }

    // Remove salt and pepper noise with median filter
    for(i = 1; i < 99; i++) {
        for(j = 1; j < 119; j++) {
            int neighbours[9] = {0}; // To store the all of the neighbours
            int n = 0; // Counter for neighbour array

            // Visit the neighbours of the current pixel
            for(k = -1; k <= 1; k++) {
                for(l = -1; l <= 1; l++) {
                    neighbours[n++] = im[i + k][j + l];
                }
            }
            
            // Sort the array
            qsort(neighbours, 9, sizeof(int), compare);

            im[i][j] = neighbours[9/2];
        }
    }

    // Iterate over the all image
    for(i = 0; i < 101; i++) {
        for(j = 0; j < 120; j++) {
            int found = 0;
            // Check if the neighbours are accesible
            if(i - 1 > 0 && j - 1 > 0 && i + 1 < 100 && j + 1 < 119) {
                found = 1;
                // Run the kernel
                for(k = -1; k <= 1; k++) {
                    for(l = -1; l <= 1; l++) {
                        if(kernel[k + 1][l + 1] == '1' && im[i + k][j + l] != '1') {
                            found = 0;
                            break;
                        }
                    }
                }
            }

            out[i][j] = found ? '1' : '0';
        }
    } 
    
    // Substract output from original
    for(i = 0; i < 100; i++) {
        for(j = 0; j < 120; j++) {
            if(im[i][j] == out[i][j]) {
                out[i][j] = '0';
            } else {
                 out[i][j] = im[i][j];
            }
        }
    }

    // Show the result
    for(i = 0; i < 100; i++) {
        for(j = 0; j < 120; j++) {
            printf("%c", out[i][j] == '0' ? ' ' : '#');
        }
        printf("\n");
    }


    // Free the memory
    for(i = 0; i < 101; i++) {
        free(im[i]);
        free(out[i]);
    }

    free(im);
    free(out);
    
    return 0;
}
