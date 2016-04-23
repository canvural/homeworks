#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main()
{
    srand(time(NULL));

    Tree *T1 = malloc(sizeof(Tree));
    Tree *T2 = malloc(sizeof(Tree));

    T1->root = NULL;
    T2->root = NULL;

    int N = 0, i;

    printf("Enter number of nodes for Tree1: ");
    scanf("%d", &N);

    printf("Randomly generated data for Tree1: ");

    for(i = 0; i < N; i++) {
        int value = rand() % 900 + 100;
        printf("%d ", value);

        insert(value, T1);
    }

    printf("\n\n");

    printf("TREE 1 TRAVERSAL: ");
    display(T1->root);
    printf("\n");

    balance_status(T1);

    printf("\n=============================\n\n");

    int fixed[] = {200, 300, 150, 350, 250, 140, 175};

    printf("Fixed data for T2: ");
    for(i = 0; i < 7; i++) {
        insert(fixed[i], T2);
        printf("%d ", fixed[i]);
    }

    printf("\n\n");

    printf("TREE 2 TRAVERSAL: ");
    display(T2->root);
    printf("\n");

    balance_status(T2);

    printf("\n\nMaking T1 empty..\n");
    make_empty(T1->root);

    printf("\nMaking T2 empty..\n");
    make_empty(T2->root);

    return 0;
}

void insert(int value, Tree *tree)
{
    Node *node = new_node(value);

    if(tree->root == NULL) {
        tree->root = node;
        return;
    }

    Node *prev = NULL, *ptr = tree->root;
    char type = ' ';
    while(ptr) {
        prev = ptr;
        if(value < ptr->data) {
            ptr = ptr->left;
            type = 'l';
        } else {
            ptr = ptr->right;
            type = 'r';
        }
    }
    if(type == 'l')
        prev->left  = node;
    else
        prev->right = node;
}

Node *new_node(int value)
{
    Node *n = malloc(sizeof(Node));
    if(NULL == n) {
        printf("Can't allocate memory for new node!");
        exit(1);
    }

    n->data = value;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void balance_status(Tree *tree)
{
    int left_depth  = max_depth(tree->root->left);
    int right_depth = max_depth(tree->root->right);

    int status = left_depth - right_depth;

    if(status > -1 && status < 1) {
        printf("Tree is BALANCED");
    } else {
        printf("Tree is UNBALANCED");
    }
}

int max_depth(Node *p)
{
    if (!p) return 0;

    int left_height  = max_depth(p->left);
    int right_height = max_depth(p->right);

    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

void make_empty(Node *p)
{
    if (p == NULL) return;

    make_empty(p->left);
    make_empty(p->right);

    free(p);
}

void display(Node *p)
{
  int i;

  if(p == NULL) return;

  display(p->left);
  printf("%d ", p->data);
  display(p->right);
}
