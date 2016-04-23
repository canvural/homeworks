#include <stdio.h>  // I/O
#include <stdlib.h> // malloc, free
#include <string.h> // memcpy

#include "list.h"

/**
 * Initializes a new list.
 *
 */
void new_list(list *list, size_t element_size)
{
	list->list_size = 0;
	list->element_size = element_size;
	list->head = list->tail = NULL;
}

/**
 * Adds a new element with data, to list, l.
 */
int add_to_list(list *l, void *data)
{
	element *e = malloc(sizeof(element));
	if(NULL == e) {
		fprintf(stderr, "Can't allocate memory for element!");
		return 1;
	}

	e->data = data;

	e->next = NULL;

	if(l->list_size == 0) {
		l->head = l->tail = e;
	} else {
		l->tail->next = e;
		l->tail = e;
	}

	l->list_size++;

	return 0;
}