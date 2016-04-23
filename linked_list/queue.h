#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

struct queue {
    struct linked_list *list;
};

struct queue *new_queue();
int queue_empty(struct queue *queue);
int queue_size(struct queue *queue);
void display_queue(struct queue *queue);
void enqueue(struct node* elem, struct queue *queue);
struct node *qfront(struct queue *queue);
struct node *qback(struct queue *queue);
void dequeue(struct queue *queue);
void delete_queue(struct queue *queue);
#endif
