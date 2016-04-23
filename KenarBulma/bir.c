#include <stdio.h>
#include <stdlib.h>

#include "image.h"

void print_image(char **im)
{
    int i, j;
    
    for(i = 0; i < 100; i++) {
        for(j = 0; j < 120; j++) {
            printf("%c", im[i][j] == '0' ? ' ' : '#');
        }
        printf("\n");
    }
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
	
	char **out = malloc(101 * sizeof(char *));
	for(i = 0; i < 101; i++)
    	out[i] = malloc(120 * sizeof(char));

    print_image(im);

    // Fill the borders of output image. Because the implementation
    // skips the borders to avoid accessing unreachable memory areas.
    for(i = 0; i < 100; i++) {out[i][0] = '0';}   // Left 
    for(i = 0; i < 120; i++) {out[0][i] = '0';}   // Top
    for(i = 0; i < 120; i++) {out[99][i] = '0';}  // Bottom
    for(i = 0; i < 100; i++) {out[i][119] = '0';} // Right

    // Remove noise by using modified median filter
    // Original algorithm sorts the neighbours and takes the middle
    // value as the pixels new value.
    // But since we only got 0's and 1's we can just check for
    // which value is in majority.
    for(i = 1; i < 99; i++) {
        for(j = 1; j < 119; j++) {
            int zeroCount = 0,
                oneCount = 0;
            
            // Visit the neighbours of the current pixel
            // and count the zeros and ones
            for(k = -1; k <= 1; k++) {
                for(l = -1; l <= 1; l++) {
                    if(im[i + k][j + l] == '0') {
                        zeroCount++;
                    } else {
                        oneCount++;
                    }
                }
            }

            // If a pixel value of 1 is surrounded by more than 5
            // pixels of 0, then its a noise and should be 0.
            // And vice-versa
            if(im[i][j] == '1' && zeroCount > 5) {
                im[i][j] = '0';
            } else if(im[i][j] == '0' && oneCount > 5) {
                im[i][j] = '1';
            }
        }
    }

    // Iterate over the all image
    for(i = 1; i < 99; i++) {
        for(j = 1; j < 119; j++) {
            char o = '0';
            
            int match = 1;

            // Iterate over all 8 neighbours of the image
            // and compare it with the element of kernel.
            // If the kernel element is 1 image should be 1 too
            // to match with kernel. If not that means that pixel
            // doesn't match with the kernel.
            for(k = -1; k <= 1; k++) {
                for(l = -1; l <= 1; l++) {
                    if(kernel[k + 1][l + 1] == '1' && im[i + k][j + l] != '1') {
                        match = 0;
                        break;
                    }
                }
            }

            if(match) {
                o = '1';
            }
            
            out[i][j] = o;
        }
    } 

    // Apply the difference of two images
    // Out = im - out
    for(i = 1; i < 99; i++) {
        for(j = 1; j < 119; j++) {
            if(im[i][j] == out[i][j]) {
                out[i][j] = '0';
            } else {
                 out[i][j] = im[i][j];
            }
        }
    }

    // Print a seperator line
    // before printing output image
    for(i = 0; i < 120; i++) {
        printf("-");
    }
    printf("\n");

    print_image(out);

    // Free the memory
    for(i = 0; i < 101; i++) {
        free(im[i]);
        free(out[i]);
    }

    free(im);
    free(out);
    
    return 0;
}
