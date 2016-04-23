#ifndef LIST_H
#define LIST_H

struct file {
  char fname[65];
  char owner[33];
  int size;
};

struct node {
  struct file data;
  struct node *next;
};

struct linked_list {
  struct node *head;
  struct node *tail;
  int size;
};

void display_file(struct file f);
struct node *new_node(struct file f);
struct linked_list *new_list();
int list_empty(struct linked_list *list);
int list_size(struct linked_list *list);
void display_list(struct linked_list *list);
void push_front(struct node* elem, struct linked_list *list);
void push_back(struct node* elem, struct linked_list *list);
struct node *front(struct linked_list *list);
struct node *back(struct linked_list *list);
void pop_front(struct linked_list *list);
void pop_back(struct linked_list *list);
void delete_list(struct linked_list *list);


#endif
