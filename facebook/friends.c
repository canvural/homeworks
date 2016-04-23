/**
 * Functions for friend related actions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"
#include "list.h"

int add_friends(char *friends, list *people);
int remove_friends(char *friends, list *people);
int block_user(char *friends, list *people);
int unblock_user(char *friends, list *people);
int list_friends_same_university(char *p, list *people);
int list_all_friends(char *p, list *people);
int list_common(char *peep, list *people);
int message(char *rest, list *people);
int is_friends(person *f, person *s);

/**
 * Adds friend to one person.
 * 
 * Return -1 for adding yoursel as friend.
 * 1 for error
 * 0 for success
 */
int add_friends(char *friends, list *people)
{
	char *first  = strtok(friends, ",");
	char *second = strtok(NULL, ",");
	printf("ADDING FRIENDS: %s %s %s\n", first, second, friends);
	if(strcmp(first, second) == 0) {
		return -1;
	}

	person *first_p = get_person_by_name(first, people);
	if(NULL == first_p) {
		fprintf(stderr, "Can't add friend to \"%s\" because he/she does not exist!", first);
		return 1;
	}

	person *second_p = get_person_by_name(second, people);
	if(NULL == second_p) {
		fprintf(stderr, "Friend %s does not exist!\n", second);
		return 1;
	}

	int f = is_friends(first_p, second_p);
	if(!f) {
		printf("%s has been already friend with %s\n", first_p->name, second_p->name);
		return 1;
	}

	add_to_list(&first_p->friend_list, second_p);
	add_to_list(&second_p->friend_list, first_p);

	printf("%s is now friends with %s\n", first_p->name, second_p->name);

	return 0;
}

int remove_friends(char *friends, list *people)
{
	char *first  = strtok(friends, ",");
	char *second = strtok(NULL, ",");

	person *first_p = get_person_by_name(first, people);
	if(NULL == first_p) {
		fprintf(stderr, "Can't add friend to \"%s\" because he/she does not exist!", first);
		return 1;
	}

	person *second_p = get_person_by_name(second, people);
	if(NULL == second_p) {
		fprintf(stderr, "Friend %s does not exist!\n", second);
		return 1;
	}

	int f = is_friends(first_p, second_p);
	if(f) {
		printf("%s and %s have not been friends!\n", first_p->name, second_p->name);
		return 1;
	}

	// Remove the friendship
	element **friend = &(first_p->friend_list.head);
	while(NULL != *friend) {
		person *other = (*friend)->data;

		if(strcmp(other->name, second_p->name) == 0) {
			element *next = (*friend)->next;
			free(*friend);
			*friend = next;
			first_p->friend_list.list_size--;
		}

		friend = &(*friend)->next;
	}

	friend = &(second_p->friend_list.head);
	while(NULL != *friend) {
		person *other = (*friend)->data;

		if(strcmp(other->name, first_p->name) == 0) {
			element *next = (*friend)->next;
			free(*friend);
			*friend = next;
			second_p->friend_list.list_size--;
		}

		friend = &(*friend)->next;
	}

	printf("%s and %s are not friends anymore!\n", first_p->name, second_p->name);

	return 0;
}

/**
 * Returns zero if two people are friends, non-zero otherwise
 */
int is_friends(person *f, person *s)
{
	element *friend = f->friend_list.head;
	while(NULL != friend) {
		person *other = friend->data;

		if(strcmp(other->name, s->name) == 0) {
			return 0;
		}

		friend = friend->next;
	}

	return 1;
}

int block_user(char *friends, list *people)
{
	char *first  = strtok(friends, ",");
	char *second = strtok(NULL, ",");

	person *first_p = get_person_by_name(first, people);
	if(NULL == first_p) {
		fprintf(stderr, "Can't add friend to \"%s\" because he/she does not exist!", first);
		return 1;
	}

	person *second_p = get_person_by_name(second, people);
	if(NULL == second_p) {
		fprintf(stderr, "Friend %s does not exist!\n", second);
		return 1;
	}

	if(first_p->blocked_list[second_p->id]) {
		printf("%s has already blocked %s\n", first_p->name, second_p->name);
		return 1;
	}
	first_p->blocked_list[second_p->id] = 1;

	printf("%s blocked %s\n", first_p->name, second_p->name);

	return 0;
}

int unblock_user(char *friends, list *people)
{
	char *first  = strtok(friends, ",");
	char *second = strtok(NULL, ",");

	person *first_p = get_person_by_name(first, people);
	if(NULL == first_p) {
		fprintf(stderr, "\"%s\" does not exist!", first);
		return 1;
	}

	person *second_p = get_person_by_name(second, people);
	if(NULL == second_p) {
		fprintf(stderr, "Friend %s does not exist!\n", second);
		return 1;
	}

	if(!first_p->blocked_list[second_p->id]) {
		printf("%s has already unblocked %s\n", first_p->name, second_p->name);
		return 1;
	}
	first_p->blocked_list[second_p->id] = 0;

	printf("%s unblocked %s\n", first_p->name, second_p->name);

	return 0;
}

int list_friends_same_university(char *p, list *people)
{
	person *pp = get_person_by_name(p, people);
	if(NULL == pp) {
		fprintf(stderr, "\"%s\" does not exist!", p);
		return 1;
	}

	printf("%s friends with same university:\n", pp->name);

	element *friend = pp->friend_list.head;
	while(NULL != friend) {
		person *other = friend->data;

		if(strcmp(other->university, pp->university) == 0) {
			if(!pp->blocked_list[other->id])
				printf("\t%s\n", other->name);
		}

		friend = friend->next;
	}

	return 0;
}

int list_all_friends(char *p, list *people)
{
	person *pp = get_person_by_name(p, people);
	if(NULL == pp) {
		fprintf(stderr, "\"%s\" does not exist!", p);
		return 1;
	}

	if(pp->friend_list.list_size == 0) {
		printf("%s has no friends\n", pp->name);
		return 1;
	}

	printf("%s's friends:\n", pp->name);

	element *friend = pp->friend_list.head;
	while(NULL != friend) {
		person *other = friend->data;

		if(!pp->blocked_list[other->id])
				printf("\t%s\n", other->name);

		friend = friend->next;
	}

	return 0;
}

int list_common(char *peep, list *people)
{
	char *first  = strtok(peep, ",");
	char *second = strtok(NULL, ",");

	person *first_p = get_person_by_name(first, people);
	if(NULL == first_p) {
		fprintf(stderr, "Can't add friend to \"%s\" because he/she does not exist!", first);
		return 1;
	}

	person *second_p = get_person_by_name(second, people);
	if(NULL == second_p) {
		fprintf(stderr, "Friend %s does not exist!\n", second);
		return 1;
	}

	printf("%s and %s got these common friends:\n", first_p->name, second_p->name);

	element *friend = first_p->friend_list.head;
	int gcf = 0;
	while(NULL != friend) {
		person *other = friend->data;

		if(!is_friends(other, second_p)) {
			gcf = 1;

			if(!first_p->blocked_list[other->id])
				printf("\t%s\n", other->name);
		}

		friend = friend->next;
	}

	if(!gcf) {
		printf("%s and %s don't have common friends!", first_p->name, second_p->name);
	}

	return 0;
}

int message(char *rest, list *people)
{
	char *first  = strtok(rest, ",");
	char *second = strtok(NULL, ",");
	char *message = strtok(NULL, ",");

	person *first_p = get_person_by_name(first, people);
	if(NULL == first_p) {
		fprintf(stderr, "Can't add friend to \"%s\" because he/she does not exist!", first);
		return 1;
	}

	person *second_p = get_person_by_name(second, people);
	if(NULL == second_p) {
		fprintf(stderr, "Friend %s does not exist!\n", second);
		return 1;
	}

	if(second_p->blocked_list[first_p->id]) {
		printf("Message cannot be sent. %s has already blocked %s!\n", second_p->name, first_p->name);
		return 1;
	}

	printf("%s sent message to %s: %s\n", first_p->name, second_p->name, message);

	return 0;
}