/**
 *
 * A simple linked list implementation on my own.
 */

#ifndef LIST_H_
#define LIST_H_

typedef struct _element {
	void *data;
	struct _element *next;
} element;

typedef struct _list {
	int list_size;
	size_t element_size;
	element *head;
	element *tail;
} list;

void new_list(list *list, size_t element_size);
int add_to_list(list *l, void *data);

#endif