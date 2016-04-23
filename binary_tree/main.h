typedef enum boolean_ {true, false} Boolean;
typedef enum publish_types {Book_t, Periodical_t, Encyclopedia_t, Null_t} PType;

typedef struct book_ {
    char *name;
    char author[41];
    int price;
    Boolean is_in_stock;
} Book;

typedef struct periodical_ {
    char *name;
    char editor[41];
    float price;
    Boolean is_in_stock;
    int vol_no;
} Periodical;

typedef struct encyclopedia_ {
    char *name;
    char publisher[41];
    int price;
    Boolean is_in_stock;
} Encyclopedia;

typedef struct node_ {
    PType type;
    char key[61];
    void *data;
    struct node_ *left;
    struct node_ *right;
} Node;


char *read_line(FILE *file);
Book *new_book(char name[], char author[], int price, Boolean in_stock);
Periodical *new_periodical(char name[], char editor[], int price, Boolean in_stock, int vol);
Encyclopedia *new_encyclopedia(char name[], char publisher[], int price, Boolean in_stock);
Node *new_node(PType type, void *data);
Node *new_tree();
Node *insert(Node *root, Node *to_add);
Node *delete_node(Node *tree, Node *to_delete);
static Node *delete_largest(Node *tree);
char *get_name(PType type, void *data);
void print_tree(Node *r, int l);
void display_node(Node *node);
void display_book(Node *node);
void display_periodical(Node *node);
void display_encyclopedia(Node *node);
