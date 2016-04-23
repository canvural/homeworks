#ifndef MAIN_H
#define MAIN_H

typedef struct node_ {
    int data;
    struct node_ *left;
    struct node_ *right;
} Node;

typedef struct tree_ {
    Node *root;
} Tree;

void insert(int value, Tree *tree); // Non-recursive
void balance_status(Tree *tree); // Non-recursive
void display(Node *p); // Recursive (in-order)
int max_depth(Node * p); // Recursive (post-order)
void make_empty(Node * p); // Recursive (post-order)
Node *new_node(int value);

#endif
