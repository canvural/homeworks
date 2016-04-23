#include <stdio.h>
#include <stdlib.h>

char **image() 
{	
	int r=101,c=121; //numbers for rows and columns
	
	FILE *file; //file pointer
	int x,y; // loop variables
	char **im=(char **) malloc(r*sizeof(char *)); //image
	for(x=0; x<r; x++)
    	im[x]=(char *) malloc(c*sizeof(char));
	
   file = fopen("noise.txt" , "r"); //open image for reading
   if (file == NULL)  // error while opening
    	printf("!!! DOSYA ACILAMADI. DOSYA ISMI image.txt OLMALIDIR. !!!");

    for(x=0; x<100; x ++) 
        fread(im[x],sizeof(char),c,file);
					
   fclose(file); // close file
   
   return im;
}
