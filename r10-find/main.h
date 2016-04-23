#ifndef MAIN_H_
#define MAIN_H_

//###############################
//#### VARIABLE DECLARATIONS ####
//###############################

// Input file name
char *input_file_name,
// Output file name
*output_file_name,
// Searh word
*search,
// Replace word
*replace;

// File handles for input and output file name
FILE *input_f,
	 *output_f;

// Flag for replace. Set when -r option is specified.
int freplace;

// Flag for output filename. Set when -o option is specified.
int foutput;

// Used for command line parsing
extern char *optarg;
extern int optind;
int c; 

//#############################
//#### FUNCTION DEFINITONS ####
//#############################


#endif //MAIN_H_