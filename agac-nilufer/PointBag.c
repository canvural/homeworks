#include <stdio.h>

#include "PointBag.h"

void PointBag_Insert(PointBag *bag, int p) {

	bag->data[bag->n] = p;
	bag->invd[p] = bag->n;
	bag->n ++;
}

void PointBag_Delete(PointBag *bag, int p) {

	int q;

	q = bag->data[bag->n-1];
	bag->data[bag->invd[p]] = q;
	bag->invd[q] = bag->invd[p];
	bag->n --;
}

/* Auxillary Methods */
void PointBag_initialize(PointBag *bag) {

	bag->n = 0;
}

void PointBag_finalize (PointBag *bag) {

	/* nothing to do */
}

void PointBag_print(PointBag *bag) {

	int i;

	if(bag->n) {

		printf("{ %d", bag->data[0]);
		for(i=1; i<bag->n; i++) { printf(", %d", bag->data[i]); }
		printf(" }");
	}
	else { printf("{}\n"); }
}
