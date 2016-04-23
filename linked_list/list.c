#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct linked_list *new_list()
{
    struct linked_list *list = malloc(sizeof(struct linked_list));
    if(NULL == list) {
        fprintf(stderr, "Can't allocate memory for new list!");
        return NULL;
    }

    list->size = 0;
    list->head = list->tail = NULL;

    return list;
}

struct node *new_node(struct file f)
{
    struct node *node = malloc(sizeof(struct node));
    if(NULL == node) {
        fprintf(stderr, "Can't allocate memory for new node!");
        return NULL;
    }

    node->data = f;
    node->next = NULL;

    return node;
}

void push_front(struct node *elem, struct linked_list *list)
{
    if(list->size == 0) {
        list->head = list->tail = elem;
    } else {
        elem->next = list->head;
        list->head = elem;
    }

    list->size++;
}

void push_back(struct node *elem, struct linked_list *list)
{
    if(list->size == 0) {
        list->head = list->tail = elem;
    } else {
        list->tail->next = elem;
        list->tail = elem;
    }

    list->size++;
}

struct node *front(struct linked_list *list)
{
    return list->head;
}

struct node *back(struct linked_list *list)
{
    return list->tail;
}

int list_empty(struct linked_list *list)
{
    return 1 ? list->size == 0 : 0;
}
int list_size(struct linked_list *list)
{
    return list->size;
}

void pop_front(struct linked_list *list)
{
    struct node *n = list->head;
    list->head = n->next;

    free(n);

    list->size--;
}

void pop_back(struct linked_list *list)
{
    struct node *temp = list->head;
    struct node *t;

    while(temp->next != NULL)
    {
        t = temp;
        temp = temp->next;
    }
    free(t->next);
    t->next = NULL;
    list->tail = t;

    list->size--;
}

void delete_list(struct linked_list *list)
{
    struct node *head = list->head;
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = temp->next;
        free(temp);
        list->size--;
    }

    free(list);
}

void display_file(struct file f)
{
    printf("%s\t%s\t%d\n", f.fname, f.owner, f.size);
}

void display_list(struct linked_list *list)
{
    if(list_empty(list)) {
        printf("List is empty!\n");
        return;
    }

    struct node *temp = list->head;
    while(temp != NULL)
    {
        display_file(temp->data);
        temp = temp->next;
    }
}
