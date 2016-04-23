#include <stdio.h> // I/O
#include <stdlib.h> // free
#include <string.h> // free

#include "list.h"
#include "utils.h"
#include "person.h"

char *commands_file = "commands.txt";

#define DEBUG 1

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