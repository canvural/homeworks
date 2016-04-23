/**
 * stack.h
 * 
 * Implementation of basic array stack.
 *
 * This implemantation is uses a simple array.
 * To access the array and to implement a stack
 * we use functions instead of directly accessing it.
 */

// Number of max elemnts one stack can hold
#define MAX 20

// Stack for first army
int first_army[MAX];

// Stack for second army
int second_army[MAX];

// Current size of stacks
int size_first_stack;
int size_second_stack;

// Stack pointer for first army's stack.
// Stores the array index of the element at the top of the stack.
int first_stack_pointer;

// Stack pointer for second army's stack.
// Stores the array index of the element at the top of the stack.
int second_stack_pointer;



// Adds soldier to the top of the stack.
int push_first_stack(int soldier);
int push_second_stack(int soldier);

// Gets the top soldier from stack.
int pop_first_stack();
int pop_second_stack();

// Gets the top soldier from stack without removing it from stack.
int top_first_stack();
int top_second_stack();