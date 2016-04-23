#include <stdio.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "utils.h"

// Remove the comment if you want to run in DEBUG mode
// or pass DEBUG to -D flag
//#define DEBUG

#ifdef DEBUG
#define debug(M, ...) fprintf(stderr, "%s", M)
#else
#define debug(M, ...)
#endif

int main()
{
	srand(time(NULL));
	
	// Players score
	int score = 0;
	
	// Players current answer
	char answer[5];
	
	// Current randomly selected word
	char current_word[5];
	
	// Read kelimeler.txt and store each line as element in array
	char word_list[5120][5];
	read_words(word_list);
	
	char create_hashtable_f;

	printf("Do you want to create the hashtable? (Y/n): ");
	scanf("%c", &create_hashtable_f);

	if(create_hashtable_f == 'y' || create_hashtable_f == 'Y') {
		
	} else {
		char hashtable_file_name[80];
		printf("Enter the name of hash table file: ");
		scanf("%80s", hashtable_file_name);
	}
	
	strcpy(current_word, word_list[rand() % 5120]);
	
	printf("Your word is: %s\nEnter an anagram: ", current_word);
	scanf("%4s", answer);
	
	if(!check_anagram(current_word, answer)) {
		printf("%s is not an anagram!\n", answer);
		score -= 5;
	}
	
    return 0;
}

