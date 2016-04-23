#include <stdio.h>

#include "stack.h"

int push_first_stack(int soldier)
{
	// Check if stack is full
	if(size_first_stack == MAX) {
		fprintf(stderr, "Can't push new soldier to stack. Stack is full!\n");
		return 1;
	}

	// Put soldier to top of the array
	// Also increment stack pointer
	first_army[++first_stack_pointer] = soldier;
}

int push_second_stack(int soldier)
{
	// Check if stack is full
	if(size_second_stack == MAX) {
		fprintf(stderr, "Can't push new soldier to stack. Stack is full!\n");
		return 1;
	}

	// Put soldier to top of the array
	// Also increment stack pointer
	second_army[++second_stack_pointer] = soldier;

	return 0;
}

int pop_first_stack()
{
	// Check if stack is empty
	if(size_first_stack < 0) {
		fprintf(stderr, "Can't pop soldier from stack. Stack is empty!\n");
		return 1;
	}

	// Return the soldier on top of the array and decrement the pointer
	return first_army[first_stack_pointer--];
}

int pop_second_stack()
{
	// Check if stack is empty
	if(size_second_stack < 0) {
		fprintf(stderr, "Can't pop soldier from stack. Stack is empty!\n");
		return 1;
	}

	// Return the soldier on top of the array and decrement the pointer
	return second_army[second_stack_pointer--];
}

int top_first_stack()
{
	// Check if stack is empty
	if(size_first_stack < 0) {
		fprintf(stderr, "Can't get soldier from stack. Stack is empty!\n");
		return 1;
	}

	// Return the soldier on top of the array
	return first_army[first_stack_pointer];
}

int top_second_stack()
{
	// Check if stack is empty
	if(size_second_stack < 0) {
		fprintf(stderr, "Can't get soldier from stack. Stack is empty!\n");
		return 1;
	}

	// Return the soldier on top of the array
	return second_army[second_stack_pointer];
}