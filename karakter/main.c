#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct element_ {
	char character;
	int occurence;
	struct element_ *next;
	struct element_ *prev;
} element;

typedef struct _list {
	int list_size;
	element *head;
	element *tail;
} List;

List *char_list;

/**
 * Reads one line or 255 chars from a file
 */
char *read_line(FILE *file)
{
	if (file == NULL) {
        fprintf(stderr, "Can't open file!");
        return NULL;
    }

    // Allocate 255 byte for one line. +1 for NULL terminator.
    char *line = malloc(256);
    if (line == NULL) {
        fprintf(stderr, "Can not allocate memory for line buffer!");
        return NULL;
    }

    if(fgets(line, 256, file) != NULL) {
    	size_t ln = strlen(line) - 1;
		if (line[ln] == '\n')
		    line[ln] = '\0';
		if (line[ln - 1] == '\r')
		    line[ln - 1] = '\0';
    	return line;
    }

    // There should be an error if we are here so
    // free the allocated space and return NULL
    free(line);
    return NULL;
}

/**
 * Alloctes memory for a new double linked list.
 */
List *new_list()
{
	List *new = malloc(sizeof(List));
	if(NULL == new) {
		printf("Can't allocate memory for a new list!");
		exit(1);
	}

	new->list_size = 0;

	new->head = NULL;
	new->tail = NULL;

	return new;
}

void add_to_list_sorted(List *list, char c, int o)
{
	element *e = malloc(sizeof(element));
	if(NULL == e) {
		printf("Can't allocate memory for element!");
		exit(1);
	}

	e->character = c;
	e->occurence = o;
	e->next = NULL;
	e->prev = NULL;

	if(list->list_size == 0) {
		list->head = e;
        list->tail = e;
    } else if(c <= list->head->character) {
		e->next = list->head;
        list->head->prev = e;
        list->head = e;
	} else {
		element *iter = list->head;
		int found = 0;
	    while (iter->next != NULL) {
	    	if(iter->character >= c) {
	    		found = 1;
	    		break;
	    	}
	        iter = iter->next;
	    }

	    if(iter->character >= c) {
			found = 1;
		}
	   	
	   	if(found) {
	   		iter->prev->next = e;
	   		e->prev = iter->prev;
	   		e->next = iter;
	   		iter->prev = e;

	   	} else {
	   		list->tail->next = e;
	        e->prev = list->tail;
	        list->tail = e;
	   	}	    
	}
	
    list->list_size++;
}

element *get_char(char c)
{
	element *iter;
	for(iter = char_list->head; iter != NULL; iter = iter->next) {
		if(iter->character == c) {
			return iter;
		}
	}

	return NULL;
}

int main()
{
	char input[128];
	printf("Write input file name: ");
	scanf("%127s", input);

	char_list = new_list();

	char *line;

	FILE *input_file = fopen(input, "r");
	if(!input_file) {
		printf("Can't open input file!");
		return 1;
	}

	while((line = read_line(input_file)) != NULL) {
		int line_count = strlen(line);
		int i;
		for(i = 0; i < line_count; i++) {
			element *c = get_char(line[i]);
			if(NULL == c) {
				add_to_list_sorted(char_list, line[i], 1);
			} else {
				c->occurence++;
			}
		}

		free(line);
	}

	FILE *output = fopen("output.txt", "w");
	if(NULL == output) {
		printf("Can't open file for writing!");
		return 1;
	}

	element *iter;
	for(iter = char_list->head; iter != NULL; iter = iter->next) {
		fprintf(output, "%c, %d, %d\n", iter->character, iter->character, iter->occurence);
	}

	return 0;
}