#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "list.h"
#include "queue.h"
#include "main.h"

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Please give file name!");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if(NULL == file) {
        fprintf(stderr, "Can't open %s for reading!", argv[1]);
        return 0;
    }

    // General queue to be used while reading file
    struct queue *queue = NULL;
    char fname[65];
    char fowner[33];
    int fsize;
    struct file f;
    struct node *node;

    // One line from commands file
    char *line;

    // One of the operations (0 -10)
    int op;

    // Rest of line
    char rline[256];

    while((line = read_line(file)) != NULL) {
        sscanf(line, "%d %255[^\n]", &op, rline);

        switch(op) {
            case 0:
                if(queue == NULL) {
                    fprintf(stderr, "There is no queue to delete!");
                } else {
                    delete_queue(queue);
                }
                break;
            case 1:
                queue = new_queue();
                break;
            case 2:
                display_queue(queue);
                break;
            case 3:
                printf("Queue empty: %d\n", queue_empty(queue));
                break;
            case 4:
                printf("Queue size: %d\n", queue_size(queue));
                break;
            case 5:
                sscanf(rline, "%s %s %d", fname, fowner, &fsize);

                strncpy(f.fname, fname, 65);
                strncpy(f.owner, fowner, 33);
                f.size = fsize;

                node = new_node(f);

                enqueue(node, queue);
                break;
            case 6:
                dequeue(queue);
                break;
            case 7:
                node = qfront(queue);
                printf("Front: ");
                display_file(node->data);
                break;
            case 8:
                node = qback(queue);
                printf("Back: ");
                display_file(node->data);
                break;
            default:
                break;
        }
    }
}

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
