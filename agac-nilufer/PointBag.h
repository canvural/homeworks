#ifndef _POINT_BAG_H_
#define _POINT_BAG_H_

#define BAG_CAPACITY 100

/* Data types */
typedef struct point_bag_data { 
	
	int n; 
	int data[BAG_CAPACITY]; 
	int invd[BAG_CAPACITY];
} PointBag; 

/* Operations */
void PointBag_Insert(PointBag *bag, int p);
void PointBag_Delete(PointBag *bag, int p);

/* Auxillary methods */
void PointBag_initialize(PointBag *bag);
void PointBag_finalize(PointBag *bag);
void PointBag_print(PointBag *bag);

#endif
