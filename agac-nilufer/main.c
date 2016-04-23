#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Tree.h"

int main() {

	char line[100], *cptr;
	int b, h, p, pofc; char d;
	Tree *tree1;

	tree1 = (Tree *)malloc(sizeof(Tree));
	Tree_initialize(tree1);

	Tree_print(tree1); printf("\n\n");

	while(1) {

		printf(">> ");
		fgets(line, 100, stdin);
		cptr = strtok(line, " \n");
		if(!strcmp(cptr, "exit")) { break; }

		if(!strcmp(cptr, "InsertRoot")) {

			cptr = strtok(NULL, " \n");
			d = cptr[0];
			Tree_InsertRoot(tree1, d);
			Tree_print(tree1); printf("\n\n");
		}

		if(!strcmp(cptr, "InsertLeaf")) {

			cptr = strtok(NULL, " \n"); pofc = atoi(cptr);
			cptr = strtok(NULL, " \n"); d = cptr[0];
			Tree_InsertLeaf(tree1, pofc, d);
			Tree_print(tree1); printf("\n\n");
		}

		if(!strcmp(cptr, "DeleteLeaf")) {

			cptr = strtok(NULL, " \n"); p = atoi(cptr);
			Tree_DeleteLeaf(tree1, p);
			Tree_print(tree1); printf("\n\n");
		}

		if(!strcmp(cptr, "IsLeaf")) {

			cptr = strtok(NULL, " \n"); p = atoi(cptr);
			b = Tree_IsLeaf(tree1, p);
			printf("ans: %s\n", b?"YES":"NO");
		}

		if(!strcmp(cptr, "NodeDepth")) {

			cptr = strtok(NULL, " \n"); p = atoi(cptr);
			h = Tree_NodeDepth(tree1, p);
			printf("ans: %d\n", h);
		}

		if(!strcmp(cptr, "NodeHeight")) {

			cptr = strtok(NULL, " \n"); p = atoi(cptr);
			h = Tree_NodeHeight(tree1, p);
			printf("ans: %d\n", h);
		}

		if(!strcmp(cptr, "Height")) {

			h = Tree_Height(tree1);
			printf("ans: %d\n", h);
		}

		if(!strcmp(cptr, "Print")) {

			Tree_Print(tree1); printf("\n\n");
		}
	}

	Tree_finalize(tree1);

	return 0;
}
