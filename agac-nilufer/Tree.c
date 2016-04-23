#include <stdio.h>
#include <string.h>

#include "Tree.h"

/* Agaca d verisini kok olarak koyar */
void Tree_InsertRoot(Tree *tree, char d) {

	int p;

	p = Memory_New(&tree->memory);
	tree->data  [p] = d;
	tree->parent[p] = -1;

	tree->heights[p] = 0;
	tree->depths[p] = 0;

	PointBag_Insert(&tree->bag, p);
}

/* Agaca d verisini pofc ile belirtilen nodun bir cocugu olarak ekler */
void Tree_InsertLeaf(Tree *tree, int pofc, char d) {

	int p, i, j, h = 0;

	p = Memory_New(&tree->memory);
	tree->data  [p] = d;
	tree->parent[p] = pofc;

	tree->depths[p]  = tree->depths[pofc] + 1;
	tree->heights[p] = 0;

	PointBag_Insert(&tree->bag, p);

	i = tree->parent[p];

	while (1) {
		if(i == -1) {
			tree->heights[0] = height(tree, 0);
			break;
		}

		tree->heights[i] = height(tree, i);

		i = tree->parent[i];
	}
}

int height(Tree *tree, int p)
{
	PointBag *b = &tree->bag;

	int i, j = p, height = 0;

	for (i = p; i < b->n; i++) {
		if(tree->parent[i] == j) {
			height++;
			j = i;
		}
	}

	return height;
}

/* Agacin p ile belirtilen yapragini siler */
void Tree_DeleteLeaf(Tree *tree, int p) {

	Memory_Del(&tree->memory, p);
	PointBag_Delete(&tree->bag, p);
}

/* Agacin nodlarini (belirtecleri ile beraber) ekrana yazar */
void Tree_Print(Tree *tree) {

	int i, p, pofc;

	PointBag *bag = &tree->bag;
	for(i=0; i<bag->n; i++) {

		p = bag->data[i];
		pofc = tree->parent[p];
		if(pofc < 0) { printf("%c (%d) -> -\n", tree->data[p], p); }
		else {printf("%c (%d) -> %c (%d)\n", tree->data[p], p, tree->data[pofc], pofc); }
	}
	printf("\n");
	printf("PointBag: ");
	PointBag_print(bag);
	printf("\n");
}

/* TODO: Agacin p ile belirtilen nodu bir yaprak midir? */
int  Tree_IsLeaf(Tree *tree, int p) {

	return tree->heights[p] == 0;
}

/* TODO: Agacin p ile belirtilen nodunun derinligini hesaplar */
int Tree_NodeDepth(Tree *tree, int p) {

	return tree->depths[p];
}

/* TODO: Agacin p ile belirtilen nodunun yuksekligini hesaplar */
int Tree_NodeHeight(Tree *tree, int p) {

	return tree->heights[p];
}

/* TODO: Agacin yuksekligini hesaplar */
int  Tree_Height(Tree *tree) {

	return tree->heights[0];
}

/* Auxillary methods */
void Tree_initialize(Tree *tree)  {

	Memory_initialize(&tree->memory);
	memset(tree->heights, 0, TREE_CAPACITY * sizeof(int));
	memset(tree->depths, 0, TREE_CAPACITY * sizeof(int));
}

void Tree_finalize(Tree *tree) {

	int i, p;

	PointBag *bag = &tree->bag;
	for(i=0; i<bag->n; i++) {

		p = bag->data[i];
		Memory_Del(&tree->memory, p);
	}
}

void Tree_print(Tree *tree) {

	int i, p, pofc;

	PointBag *bag = &tree->bag;
	for(i=0; i<bag->n; i++) {

		p = bag->data[i];
		pofc = tree->parent[p];
		if(pofc < 0) { printf("%c -> -\n", tree->data[p]); }
		else {printf("%c -> %c\n", tree->data[p], tree->data[pofc]); }
	}
	printf("\n");
}

/* Memory methods */
void Memory_initialize(Memory *memory) {

	int p;
	for(p=0; p<TREE_CAPACITY; p++) { memory->occupe[p] = 0; }
}

int  Memory_New(Memory *memory) {

	int p;

	for(p = 0; p < TREE_CAPACITY; p++) {
		if(!memory->occupe[p]) {
			memory->occupe[p] = 1;
			return p;
		}
	}

	return -1;
}

void Memory_Del(Memory *memory, int p) {

	memory->occupe[p] = 0;
}

int  Memory_Occupied(Memory *memory, int p) {

	return memory->occupe[p];
}
