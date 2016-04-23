/**
 * main.c
 * 
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "utils.h"

static void usage()
{
	printf(" \n\n Usage: textprocess -f input -s search [-r replace] [-o output] [-h]\n");
	printf("\t-f : Input file name which is used for processing\n");
	printf("\t-s : Search word which we need to search in input file.\n");
	printf("\t-r : Replace word which replaced with searched one.\n");
	printf("\t-o : Output file in this case result redirect into this file.\n");
	printf("\t-h : This help text.");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	// Turn off errors as we will handle it
	opterr = 0;

	// Turn off flags by default
	foutput = freplace = 0;

	// Parse command line options
	while ((c = getopt(argc,argv,"f:s:r:o:h")) != -1) {
		switch (c) {
		case 'f':
			input_file_name = optarg;
			break;
		case 's':
			search = optarg;
			break;
		case 'r':
			freplace = 1;
			replace = optarg;
			break;
		case 'o':
			foutput = 1;
			output_file_name = optarg;
			break;
		case 'h': 
			usage();
			break;
		case '?':
		case ':':
            if (optopt == 'f' || optopt == 's' || optopt == 'r' || optopt == 'o')
            	fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
            	fprintf (stderr, "Unknown option '-%c'.\n", optopt);
            else
            	fprintf (stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
            usage();
		default:
			usage();
		}
	}

	if (optind != argc) {
		usage();
	}

	argc -= optind;
	argv += optind;

	// Check if input file exists
	input_f = fopen(input_file_name, "r");
	if(input_f == NULL) {
		fprintf(stderr, "Cannot find input file %s\n", input_file_name);
		exit(EXIT_FAILURE);
	}

	// Check if output file exists
	if(foutput) {
		output_f = fopen(output_file_name, "w+");
		if(output_f == NULL) {
			fprintf(stderr, "Cannot open output file %s\n", output_file_name);
			exit(EXIT_FAILURE);
		}
	}

	// Check if a search word is specified
	if(!search) {
		fprintf(stderr, "You have to specify a search word!\n");
		exit(EXIT_FAILURE);
	}

	if(!freplace)
		search_for_word(input_f, search);
	else {
		replace_word(input_f, search, replace);
	}

	if(foutput) {
		printf("Program searched %s from %s and wrote the ouput to %s", search, input_file_name, output_file_name);
	}

	return 0;
}