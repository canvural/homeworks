#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 5

typedef struct {
    int stack[MAX_STACK_SIZE];
    int top;
    int size;
} Stack;

// A Town node in linked list
typedef struct _node{
    char *name;
    Stack *stack;
    struct _node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  int size;
} List;

Stack *new_stack()
{
    Stack *s = malloc(sizeof(Stack));
    if(NULL == s) {
        fprintf(stderr, "Cannot allocate memory for a new stack");
        exit(1);
    }

    s->top  = -1;
    s->size = 0;

    return s;
}

Node *new_node(char name[])
{
    Node *n = malloc(sizeof(Node));
    if(NULL == n) {
        fprintf(stderr, "Cannot allocate memory for a new node");
        exit(1);
    }

    n->name = malloc(strlen(name) + 1);
    if(NULL == n->name) {
        fprintf(stderr, "Cannot allocate memory for a new name");
        exit(1);
    }
    strncpy(n->name, name, strlen(name));

    n->stack = new_stack();
    n->next = NULL;

    return n;
}

List *new_list()
{
    List *list = malloc(sizeof(List));
    if(NULL == list) {
        fprintf(stderr, "Can't allocate memory for new list!");
        return NULL;
    }

    list->size = 0;
    list->head = list->tail = NULL;

    return list;
}

int push(Stack *stack, int to_add)
{
    if(stack->size == MAX_STACK_SIZE) {
        fprintf(stderr, "Cannot push element. Stack is full!\n");
        return 1;
    }

    stack->stack[++stack->top] = to_add;
    stack->size++;

    return 0;
}

int pop(Stack *stack)
{
    if(stack->size < 0) {
        fprintf(stderr, "Cannot pop element. Stack is empty!\n");
        return -1;
    }

    stack->size--;

    return stack->stack[stack->top--];
}

void add_to_list(List *list, Node *to_add)
{
    if(list->size == 0) {
        list->head = list->tail = to_add;
    } else {
        list->tail->next = to_add;
        list->tail = to_add;
    }

    list->size++;
}

Node *get_node_by_name(List *list, char name[])
{
    Node *temp = list->head;

    while(temp != NULL) {
        if(strcmp(temp->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

int main()
{
    FILE *towns = fopen("towns.txt", "r");
    if(NULL == towns) {
        fprintf(stderr, "Cannot read 'towns.txt'");
        return 1;
    }

    FILE *transactions = fopen("transactions.txt", "r");
    if(NULL == transactions) {
        fprintf(stderr, "Cannot read 'transactions.txt'");
        return 1;
    }

    List *town_list = new_list();
    if(NULL == town_list) {
        return 1;
    }

    char town_name_temp[256];
    Node *temp_node = NULL;

    while(fscanf(towns, "%s", town_name_temp) != EOF) {
        temp_node = new_node(town_name_temp);

        add_to_list(town_list, temp_node);
    }

    fclose(towns);

    char town_name[256];
    char operation[8];
    int data;

    while(fscanf(transactions, "%s %s %d", town_name, operation, &data) != EOF) {
        temp_node = get_node_by_name(town_list, town_name);
        if(NULL == temp_node) {
            fprintf(stderr, "Town '%s' cannot found in list!\n", town_name);
            continue;
        }

        if(strcmp(operation, "ADD") == 0) {
            // ADD
            push(temp_node->stack, data);
        } else {
            // DELETE
            pop(temp_node->stack);
        }
    }

    fclose(transactions);

    temp_node = town_list->head;

    while(temp_node != NULL) {
        if(temp_node->stack->size == 0) {
            temp_node = temp_node->next;
            continue;
        }

        printf("TOWN: %s\n", temp_node->name);

        while(temp_node->stack->size > 0) {
            printf("\t%d\n", pop(temp_node->stack));
        }

        temp_node = temp_node->next;
    }

    return 0;
}
