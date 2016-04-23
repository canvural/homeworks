#include <stdio.h>
#include <string.h>

#include "main.h"
#include "stack.h"

int main()
{
	// First, first army starts
	turn = 1;

	dead_count =
	dead_count_ =
	damage_count =
	damage_count_ = 0;

	// One line of txt file
	char *line;

	// Loop until we reach the end of file
	while((line = read_line()) != NULL) {
		// If the size of the line is greater than 1
		// it means we got a ADD command
		if(strlen(line) > 1) {
			if(sscanf(line, "%c %d %s", &command, &army, soldier_info) == 3) {
				printf("Adding soldiers to army %d\n", army);

				char *buf;

				buf = strtok(soldier_info, ";");
				while(NULL != buf) {
					int health, strength;
					sscanf(buf, "%d,%d", &health, &strength); // should check for errors...
					printf("\tS - H: %d S: %d\n", health, strength);

					// Add soldier to its stack
					if(army == 1) {
						push_first_stack(concatenate(health, strength));
						size_first_stack++;
					} else if (army == 2) {
						push_second_stack(concatenate(health, strength));
						size_second_stack++;
					}
					buf = strtok(NULL, ";");
				}
			}
			else {
				fprintf(stderr, "Syntax of file is wrong!\n");
			}
		} else if(strcmp(line, "F") == 0) {
			// FIGHT

			// End the war if there is no soldier
			if(size_first_stack == 0 || size_second_stack == 0) {
				printf("War ended!\n");
				continue;
			}

			float damage;
			int new_health;

			// Calculate damage for soldiers and HIT!

			// For first army's soldier
			if(turn) {
				// Pop only second army's soldier from stack.
				// The reason for using pop instead of top is
				// to be able to update the soldier's health.
				int soldier = top_first_stack(),
					soldier_ = pop_second_stack();

				// Extract health and strength from soldiers
				// First three digit is health, last three digit is strength
				int health = soldier / 1000,
				strength = soldier - soldier / 1000 * 1000,
				health_ = soldier_ / 1000,
				strength_ = soldier_ - soldier_ / 1000 * 1000;

				// Calculate damage
				damage = (strength - strength_) * 0.05 + 50;

				// Print the hit!
				printf("1 hit %f damage\n", damage);
				damage_count += damage;

				// New health for second army's soldier after hit
				new_health = health_ - damage;

				// Add soldier back to stack if he is not dead!
				if(new_health > 0) {
					push_second_stack(concatenate(new_health, strength_));
				}
				// Soldier is dead. RIP
				else {
					printf("2 has a casualty\n");
					size_second_stack--;
					dead_count_++;
				}

				// change turns
				turn = 0;
			}
			// For second army's soldier
			else {
				// Pop only first army's soldier from stack.
				// The reason for using pop instead of top is
				// to be able to update the soldier's health.
				int soldier = pop_first_stack(),
					soldier_ = top_second_stack();

				// Extract health and strength from soldiers
				// First three digit is health, last three digit is strength
				int health = soldier / 1000,
				strength = soldier - soldier / 1000 * 1000,
				health_ = soldier_ / 1000,
				strength_ = soldier_ - soldier_ / 1000 * 1000;

				// Calculate damage
				damage = (strength_ - strength) * 0.05 + 50;

				// Print the hit!
				printf("2 hit %f damage\n", damage);
				damage_count_ += damage;

				// New health for first army's soldier after hit
				new_health = health - damage;

				// Add soldier back to stack if he is not dead!
				if(new_health > 0) {
					push_first_stack(concatenate(new_health, strength));
				}
				// Soldier is dead. RIP
				else {
					printf("1 has a casualty\n");
					size_first_stack--;
					dead_count++;
				}

				// change turns
				turn = 1;
			}
		} else if(strcmp(line, "C") == 0) {
			// CRITICAL HIT

			if(turn) {
				// Soldier from first army attacking
				// Kill the soldier from second army
				int dummy = pop_second_stack();

				printf("Critical shot!\n2 has a casualty!\n");
				size_second_stack--;
				dead_count_++;

				// change turns
				turn = 0;
			} else {
				// Soldier from second army attacking
				// Kill the soldier from first army
				int dummy = pop_first_stack();

				printf("Critical shot!\n1 has a casualty!\n");
				size_first_stack--;
				dead_count++;

				// change turns
				turn = 1;
			}
		} else if(strcmp(line, "S") == 0) {
			// STATISTICS

			printf("1 has %d soldier left, %d soldiers died!\n", size_first_stack, dead_count);
			printf("2 has %d soldier left, %d soldiers died!\n", size_second_stack, dead_count_);

			printf("1 harmed %f total damage\n", damage_count);
			printf("2 harmed %f total damage\n", damage_count_);
		}
	}

	return 0;
}

char *read_line() 
{ 
	static FILE *file; 
	
	if(file == NULL) {
		file = fopen (filename, "r");
	}

	if ( file != NULL ) { 
		if(fgets(lineG, sizeof(lineG), file) != NULL) {
			// One little addition
			// Clean the new line character if there is one
			size_t ln = strlen(lineG) - 1;
			if (lineG[ln] == '\n')
			    lineG[ln] = '\0';

			return lineG;
		}
		else {
			fclose ( file );
		} 
	}
	else {
		perror(filename);
	}

	return NULL; 
}

// Little math trick to concat two integer
int concatenate(int x, int y) {
    int pow = 10;
    while(y >= pow)
        pow *= 10;
    // This is for strength values below 100
    if(y < 100)
    	pow *= 10;
    return x * pow + y;        
}