#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

person *new_person(char *name, int age, char *university)
{
	// Allocate space for one person
	person *p = malloc(sizeof(person));
	if(NULL == p) {
		fprintf(stderr, "Can't allocate memory for person!");
		return NULL;
	}

	// Set the person's id
	p->id = aid++;

	// Allocate memory for person's name and set it.
	p->name = malloc(strlen(name) + 1);
	if(NULL == p->name) {
		fprintf(stderr, "Can't allocate memory for person name!");
		return NULL;
	}
	strncpy(p->name, name, strlen(name));

	p->age = age;

	// Allocate memory for person's university and set it.
	p->university = malloc(strlen(university) + 1);
	if(NULL == p->university) {
		fprintf(stderr, "Can't allocate memory for person university!\n");
		return NULL;
	}
	strncpy(p->university, university, strlen(university));

	// Create an empty list for friends
	new_list(&p->friend_list, sizeof(person *));

	memset(p->blocked_list, 0, 256 * sizeof(int));

	return p;
}

int add_person_to_list(char *info, list *people)
{
	char *name = strtok(info, ",");
	int age = strtol(strtok(NULL, ","), NULL, 10);
	char *university = strtok(NULL, ",");

	if(NULL != get_person_by_name(name, people)) {
		fprintf(stderr, "%s is already added!\n", name);
		return 1;
	}
	
	person *p = new_person(name, age, university);
	if(NULL == p) {
		fprintf(stderr, "There was an error while creating new person!\n");
		return 1;
	}

	if(add_to_list(people, p)) {
		fprintf(stderr, "Can't add new person to list!\n");
		return 1;
	}

	// Succesfully added to list
	return 0;
}

person *get_person_by_name(char *name, list *people)
{
	element *current = people->head;

	while(NULL != current) {
		person *p = current->data;
		if(strcmp(p->name,
			name) == 0) {
			return p;
		}

		current = current->next;
	}

	return NULL;
}