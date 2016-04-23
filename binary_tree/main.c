#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main()
{
    FILE *file = fopen("inputbookdb.txt", "r");
    if(NULL == file) {
        fprintf(stderr, "Can't open '%s' for reading!", "inputbookdb.txt");
        return 1;
    }

    // One line from commands file
    char *line;

    // One of the of publication type
    char op;

    // Rest of line
    char rline[256];

    char *name;
    char *author;
    int price;
    float p_price;
    int vol_no;
    Boolean in_stock;

    // Create new Binary Search Tree
    Node *root = NULL;



    while((line = read_line(file)) != NULL) {
        sscanf(line, "%c %255[^\n]", &op, rline);

        switch(op) {
            case 'B':
                name     = strtok(rline, "#");
                author   = strtok(NULL, "#");
                price    = strtol(strtok(NULL, "#"), NULL, 10);
                in_stock = strcmp(strtok(NULL, "#"), " T") == 0 ? true : false;

                root = insert(root, new_node(Book_t, new_book(name, author, price, in_stock)));
                break;
            case 'P':
                name     = strtok(rline, "#");
                author   = strtok(NULL, "#");
                p_price  = strtof(strtok(NULL, "#"), NULL);
                in_stock = strcmp(strtok(NULL, "#"), " T") == 0 ? true : false;
                vol_no   = strtol(strtok(NULL, "#"), NULL, 10);

                root = insert(root, new_node(Periodical_t, new_periodical(name, author, p_price, in_stock, vol_no)));
                break;
            case 'E':
                name     = strtok(rline, "#");
                author   = strtok(NULL, "#");
                price    = strtol(strtok(NULL, "#"), NULL, 10);
                in_stock = strcmp(strtok(NULL, "#"), " T") == 0 ? true : false;

                root = insert(root, new_node(Encyclopedia_t, new_encyclopedia(name, author, price, in_stock)));
                break;
            default:
                break;
        }
    }

    int i;
    Node *current_node = root;
    Node *parent = NULL;
    char i_name[61];
    char i_author[41];
    int i_price;
    float ip_price;
    int i_vol_no;
    int stock;
    Boolean i_in_stock;

    do {
        printf("\n");
        printf("1) Display\n");
        printf("2) Go Left\n");
        printf("3) Go Right\n");
        printf("4) Go up\n");
        printf("5) Delete\n");
        printf("6) Insert\n");
        printf("7) Save\n");
        printf("8) Quit\n");
        printf("\nEnter your choice:");
        scanf("%d", &i);

        switch(i) {
            case 1:
                display_node(current_node);
                break;
            case 2:
                if(NULL != current_node->left) {
                    parent = current_node;
                    current_node = current_node->left;
                }
                else
                    printf("Current node does not have a left node!\n");
                break;
            case 3:
                if(NULL != current_node->right) {
                    parent = current_node;
                    current_node = current_node->right;
                } else
                    printf("Current node does not have a right node!\n");
                break;
            case 4:
                if(NULL == parent) {
                    printf("Current node does not have a parent node!\n");
                } else {
                    current_node = parent;
                }
                break;
            case 5:
                delete_node(root, current_node);
                current_node = root;
                break;
            case 6:
                printf("1)Book\n2)Periodical\n3)Encyclopedia\nEnter the publication type: ");
                int pt;
                scanf("%d", &pt);
                switch(pt){
                    case 1:
                        printf("Enter the book name: ");
                        scanf("%s", i_name);
                        printf("Enter the book author: ");
                        scanf("%s", i_author);
                        printf("Enter the book price: ");
                        scanf("%d", &i_price);
                        printf("Enter the book is in store: ");
                        scanf("%d", &stock);
                        root = insert(root, new_node(Book_t, new_book(i_name, i_author, i_price, stock == 1 ? true: false)));
                        break;
                    case 2:
                        printf("Enter the Periodical name: ");
                        scanf("%s", i_name);
                        printf("Enter the Periodical editor: ");
                        scanf("%s", i_author);
                        printf("Enter the Periodical price: ");
                        scanf("%f", &ip_price);
                        printf("Enter the Periodical is in store: ");
                        scanf("%d", &stock);
                        printf("Enter the Periodical vol no: ");
                        scanf("%d", &i_vol_no);
                        root = insert(root, new_node(Periodical_t, new_periodical(i_name, i_author, ip_price, stock == 1 ? true: false, i_vol_no)));
                        break;
                    case 3:
                        printf("Enter the Encyclopedia name: ");
                        scanf("%s", i_name);
                        printf("Enter the Encyclopedia publisher: ");
                        scanf("%s", i_author);
                        printf("Enter the Encyclopedia price: ");
                        scanf("%d", &i_price);
                        printf("Enter the Encyclopedia is in store: ");
                        scanf("%d", &stock);
                        root = insert(root, new_node(Encyclopedia_t, new_encyclopedia(i_name, i_author, i_price, stock == 1? true: false)));
                        break;
                    default:
                        break;
                }
                break;
            case 8:
                break;
            default:
                break;
        }
    } while(i != 8);

    return 0;
}

Book *new_book(char name[], char author[], int price, Boolean in_stock)
{
    Book *b = malloc(sizeof(Book));
    if(NULL == b) {
        printf("Can't allocate memory for new book!");
        exit(1);
    }

    b->name = malloc(strlen(name) + 1);
    strncpy(b->name, name, strlen(name));
    strncpy(b->author, author, strlen(author));
    b->price = price;
    b->is_in_stock = in_stock;

    return b;
}

Periodical *new_periodical(char name[], char editor[], int price, Boolean in_stock, int vol)
{
    Periodical *p = malloc(sizeof(Periodical));
    if(NULL == p) {
        printf("Can't allocate memory for new periodical!");
        exit(1);
    }

    p->name = malloc(strlen(name) + 1);
    strncpy(p->name, name, strlen(name));
    strncpy(p->editor, editor, strlen(editor));
    p->price = price;
    p->is_in_stock = in_stock;
    p->vol_no = vol;

    return p;
}

Encyclopedia *new_encyclopedia(char name[], char publisher[], int price, Boolean in_stock)
{
    Encyclopedia *e = malloc(sizeof(Encyclopedia));
    if(NULL == e) {
        printf("Can't allocate memory for new encyclopedia!");
        exit(1);
    }

    e->name = malloc(strlen(name) + 1);
    strncpy(e->name, name, strlen(name));
    strncpy(e->publisher, publisher, strlen(publisher));
    e->price = price;
    e->is_in_stock = in_stock;

    return e;
}

Node *new_node(PType type, void *data)
{
    Node *n = malloc(sizeof(Node));
    if(NULL == n) {
        printf("Can't allocate memory for new node!");
        exit(1);
    }

    n->type = type;
    if(data != NULL) {
        strncpy(n->key, get_name(type, data), strlen(get_name(type, data)));
    }
    n->data = data;
    n->left = NULL;
    n->right = NULL;

    return n;
}

Node *insert(Node *tree, Node *to_add)
{
    if(NULL == tree) {
        return to_add;
    }

    int cmp = strcmp(get_name(tree->type, tree->data), get_name(to_add->type, to_add->data));

    if(cmp < 0) {
        tree->left = insert(tree->left, to_add);
    } else if(cmp > 0) {
        tree->right = insert(tree->right, to_add);
    }
    
    return tree;
}

static Node *delete_largest(Node *tree){

    Node *p = tree;

    while (p->right != NULL) p = p->right;
    return p;
}

Node *delete_node(Node *tree, Node *to_delete)
{
    if(NULL == tree) return tree;

    int cmp = strcmp(get_name(tree->type, tree->data), get_name(to_delete->type, to_delete->data));

    if(cmp < 0) {
        tree->left = delete_node(tree->left, to_delete);
    } else if(cmp > 0) {
        tree->right = delete_node(tree->right, to_delete);
    } else {
        Node *p;

        if(tree->left == NULL && tree->right == NULL) {
            tree = NULL;
        } else if(tree->left == NULL) {
            tree = tree->right;
        } else if(tree->right == NULL) {
            tree = tree->left;
        } else {
            p = delete_largest(tree->left);
            tree->type = p->type;
            strncpy(tree->key, p->key, strlen(p->key));
            tree->data = p->data;
            tree->left = delete_node(tree->left, p);
        }
    }

    return tree;
}

char *get_name(PType type, void *data)
{
    switch(type) {
        case Book_t:
            return ((Book*)(data))->name;
        case Periodical_t:
            return ((Periodical*)(data))->name;
        case Encyclopedia_t:
            return ((Encyclopedia*)(data))->name;
        default:
            break;
    }

    return NULL;
}

void print_tree(Node *r, int l)
{
  int i;

  if(r == NULL) return;

  print_tree(r->right, l+1);
  for(i=0; i<l; i++) printf("*");
  printf("%s\n", get_name(r->type, r->data));
  print_tree(r->left, l+1);
}

void display_node(Node *node)
{
    switch(node->type) {
        case Book_t:
            display_book(node);
            break;
        case Periodical_t:
            display_periodical(node);
            break;
        case Encyclopedia_t:
            display_encyclopedia(node);
            break;
        default:
            break;
    }
}

void display_book(Node *node)
{
    Book *b = (Book*) (node->data);
    printf("Book Name: %s\n", b->name);
    printf("Book Author: %s\n", b->author);
    printf("Book Price: %d\n", b->price);
    printf("Book Is In Stock: %d\n", b->is_in_stock == true ? 1 : 0);
}

void display_periodical(Node *node)
{
    Periodical *b = (Periodical*) (node->data);
    printf("Periodical Name: %s\n", b->name);
    printf("Periodical Editor: %s\n", b->editor);
    printf("Periodical Price: %f\n", b->price);
    printf("Periodical Is In Stock: %d\n", b->is_in_stock == true ? 1 : 0);
    printf("Periodical Vol No: %d\n", b->vol_no);
}

void display_encyclopedia(Node *node)
{
    Encyclopedia *b = (Encyclopedia*) (node->data);
    printf("Encyclopedia Name: %s\n", b->name);
    printf("Encyclopedia Publisher: %s\n", b->publisher);
    printf("Encyclopedia Price: %d\n", b->price);
    printf("Encyclopedia Is In Stock: %d\n", b->is_in_stock == true ? 1 : 0);
}

/**
 * Reads one line or 255 chars from a file
 */
char *read_line(FILE *file)
{
    if (file == NULL) {
        fprintf(stderr, "Can't open file!");
        return NULL;
    }

    // Allocate 255 byte for one line. +1 for NULL terminator.
    char *line = malloc(256);
    if (line == NULL) {
        fprintf(stderr, "Can not allocate memory for line buffer!");
        return NULL;
    }

    if(fgets(line, 256, file) != NULL) {
        size_t ln = strlen(line) - 1;
        if (line[ln] == '\n')
            line[ln] = '\0';
        if (line[ln - 1] == '\r')
            line[ln - 1] = '\0';
        return line;
    }

    // There should be an error if we are here so
    // free the allocated space and return NULL
    free(line);
    return NULL;
}
