#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

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

void new_list(list *list, size_t element_size)
{
	list->list_size = 0;
	list->element_size = element_size;
	list->head = list->tail = NULL;
}

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

int aid;

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
	strcpy(p->name, name);

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

int add_friends(char *friends, list *people)
{
	char *first  = strtok(friends, ",");
	char *second = strtok(NULL, ",");

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

char *commands_file = "commands.txt";

int main()
{
	// Person ids starts at 1
	aid = 1;

	// A linked list for storing persons
	list people;
	new_list(&people, sizeof(person));

	FILE *commands = fopen(commands_file, "r");
	if(NULL == commands) {
		fprintf(stderr, "Can't open commands file for reading. Please make sure it exists!\n");
		return 1;
	}

	// One line from commands file
	char *line;

	// One of the commands
	char command;

	// Rest of the command
	char rcommand[256];

	// Variable for error handling
	int rc;

	while((line = read_line(commands)) != NULL) {
		sscanf(line, "%c %255[^\n]", &command, rcommand);

		switch(command) {
			case 'P':
				add_person_to_list(rcommand, &people);
				break;
			case 'F':
				rc = add_friends(rcommand, &people);
				if(rc == -1) {
					fprintf(stderr, "You cannot add yourself as your friend!\n");
				}
				break;
			case 'R':
				rc = remove_friends(rcommand, &people);
				break;
			case 'B':
				block_user(rcommand, &people);
				break;
			case 'U':
				unblock_user(rcommand, &people);
				break;
			case 'S':
				list_friends_same_university(rcommand, &people);
				break;
			case 'A':
				list_all_friends(rcommand, &people);
				break;
			case 'C':
				list_common(rcommand, &people);
				break;
			case 'M':
				message(rcommand, &people);
				break;
			default:
				break;
		}

		memset(rcommand, 0, sizeof(rcommand));

		// Free the line, since our work with it is done.
		free(line);
	}

	// CLEANUP

	element *current;

	while(NULL != people.head) {
		current = people.head;
		people.head = current->next;

		person *p = current->data;

		free(p->name);
		free(p->university);

		element *friend;
		while(NULL != p->friend_list.head) {
			friend = p->friend_list.head;
			p->friend_list.head = friend->next;

			free(friend);
		}

		free(current->data);
		free(current);
	}

	// Close our file handle
	fclose(commands);

	return 0;
}
