#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "list.h"

struct queue *new_queue()
{
    struct queue *q = malloc(sizeof(struct queue));
    if(NULL == q) {
        fprintf(stderr, "Can't allocate memory for new queue!");
        return NULL;
    }

    q->list = new_list();

    return q;
}

int queue_empty(struct queue *queue)
{
    return list_empty(queue->list);
}

int queue_size(struct queue *queue)
{
    return queue->list->size;
}

void display_queue(struct queue *queue)
{
    if(list_empty(queue->list)) {
        printf("Queue is empty!\n");
        return;
    }
    
    display_list(queue->list);
}

void enqueue(struct node* elem, struct queue *queue)
{
    push_back(elem, queue->list);
}

struct node *qfront(struct queue *queue)
{
    return front(queue->list);
}

struct node *qback(struct queue *queue)
{
    return back(queue->list);
}

void dequeue(struct queue *queue)
{
    pop_front(queue->list);
}
void delete_queue(struct queue *queue)
{
    delete_list(queue->list);

    free(queue);
}
