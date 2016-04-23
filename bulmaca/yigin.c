#include <stdio.h>
#include <stdlib.h>
#include "yigin.h"

void create(Stack s) {
	s.top = 0;
}

void close(){
}

int push(Stack *s, StackDataType newdata){
	if(s->top < STACKSIZE) {
		int i, j;
		StackDataType new;
		for(i = 0; i < 3; i++) {
			for(j = 0; j < 3; j++) {
				new.tahta[i][j] = newdata.tahta[i][j];
			}
		}
		s->element[s->top++] = new;
		return 1;
	} else {
		s->top -= 5;
		printf("yigin doldu!\n");
	}
	return 0;
}

StackDataType pop(Stack *s){
	if(s->top == 0) {
		printf("Yigin bos!\n");
		exit(1);
	}
	return s->element[--s->top];
}

int isempty(Stack s){
	return (s.top == 0) ? 1 : 0;
}
