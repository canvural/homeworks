#ifndef STACK_H
#define STACK_H
#define STACKSIZE 200000

typedef struct StackDataType_ {
	char tahta[3][3];
	int islem;
}StackDataType;

struct STACK{
	StackDataType element[STACKSIZE];
	int top;
};

typedef struct STACK Stack;

Stack yigin1, yigin2;

void create();
void close();
int push();
StackDataType pop();
int isempty();

#endif