/**
 * Definition for person data type and some helper functions
 */

#ifndef PERSON_H_
#define PERSON_H_

#include "list.h"

typedef struct person_ {
	int id;
	char *name;
	int age;
	char *university;
	// This person's friends
	list friend_list;
	// Blocked list
	int blocked_list[256];
} person;

// Auto increment id for person
int aid;

person *new_person(char *name, int age, char *university);
int add_person_to_list(char *info, list *people);
person *get_person_by_name(char *name, list *people);

#endif