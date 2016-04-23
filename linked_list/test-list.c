#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include "list.h"
#include "main.h"

int main(int argc, char *argv[])
{
    // TEST
    //test_linked_list();

    if(argc != 2) {
        printf("Please give file name!");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if(NULL == file) {
        fprintf(stderr, "Can't open %s for reading!", argv[1]);
        return 0;
    }

    // General list to be used while reading file
    struct linked_list *list = NULL;
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
                if(list == NULL) {
                    fprintf(stderr, "There is no list to delete!");
                } else {
                    delete_list(list);
                }
                break;
            case 1:
                list = new_list();
                break;
            case 2:
                display_list(list);
                break;
            case 3:
                printf("List empty: %d\n", list_empty(list));
                break;
            case 4:
                printf("List size: %d\n", list_size(list));
                break;
            case 5:
                sscanf(rline, "%s %s %d", fname, fowner, &fsize);

                strncpy(f.fname, fname, 65);
                strncpy(f.owner, fowner, 33);
                f.size = fsize;

                node = new_node(f);

                push_front(node, list);
                break;
            case 6:
                sscanf(rline, "%s %s %d", fname, fowner, &fsize);

                strncpy(f.fname, fname, 65);
                strncpy(f.owner, fowner, 33);
                f.size = fsize;

                node = new_node(f);

                push_back(node, list);
                break;
            case 7:
                pop_front(list);
                break;
            case 8:
                pop_back(list);
                break;
            case 9:
                node = front(list);
                printf("Front: ");
                display_file(node->data);
                break;
            case 10:
                node = back(list);
                printf("Back: ");
                display_file(node->data);
                break;
            default:
                break;
        }
    }

    return 0;
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

void test_linked_list()
{
    struct linked_list *list = new_list();

    assert(NULL == list->head);
    assert(0 == list_size(list));
    assert(NULL == front(list));

    struct file f;
    strncpy(f.fname, "TEST", 65);
    strncpy(f.owner, "Tester", 33);
    f.size = 128;

    struct node *node = new_node(f);

    push_front(node, list);

    display_list(list);

    struct file ff;
    strncpy(ff.fname, "TEST2", 65);
    strncpy(ff.owner, "Tester2", 33);
    ff.size = 128;

    struct node *node2 = new_node(ff);

    push_back(node2, list);

    display_list(list);

    pop_back(list);
    pop_front(list);

    display_list(list);
    delete_list(list);
}
