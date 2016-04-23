#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _el{
    int data;
    struct _el *next;
    struct _el *prev;
} Element;

typedef struct _list {
    Element *head;
    Element *tail;
} List;

void init(List *l)
{
    l->head = NULL;
    l->tail = NULL;
}

void insertHead(List *l, int x)
{
    Element *el = malloc(sizeof(Element));

    el->data = x;

    if(l->head == NULL || l->tail == NULL) {
        l->head = el;
        l->tail = el;
        
        el->next = l->head;
        el->prev = l->tail;
        
    } else {
        Element *temp = l->head;
        
        l->head = el;
        l->tail->next = el;

        temp->prev = el;
        el->next = temp;
        el->prev = l->tail;
    }
}

int deleteHead(List *l, int *value){
    if(l->head == NULL) {
        return 0;
    }
    
    if(l->head == l->tail) {
        free(l->head);
        l->head = l->tail = NULL;
        return 1;
    }
    
    Element *old = l->head;

    *value = old->data;

    l->head = old->next;
    l->head->prev = l->tail;
    l->tail->next = l->head;

    free(old);

    return 1;
}

void insertTail(List *l, int x)
{
    if(l->tail == NULL) {
        insertHead(l, x);
        return;
    }

    Element *el = malloc(sizeof(Element));

    el->data = x;
    el->next = l->head;

    Element *old = l->tail;

    l->tail = el;
    l->head->prev = el;
    el->prev = old;
    old->next = el;
}

int deleteTail(List *l, int *value)
{
    if(l->head == NULL) {
        return 0;
    }

    if(l->head == l->tail) {
        free(l->tail);
        l->head = l->tail = NULL;
        return 1;
    }
    
    Element *old = l->tail;

    *value = old->data;
    
    l->tail = old->prev;
    l->tail->next = l->head;
    l->head->prev = l->tail;    
    
    free(old);
    old = NULL;

    return 1;
}

int findValue(List *l, int value)
{
    Element *iter = l->head;
    int i = 0;

    do {    
        if(iter->data == value) {
            return i;
        }

        iter = iter->next;
        i++;
    } while(iter != l->head);

	return -1;
}

void removeAllValue(List *l, int value)
{
    if(l->head == NULL) {
        return;
    }
    
    int j;
    while((j = findValue(l, value)) != -1) {
        if(j == 0) {
            int dummy;
            deleteHead(l, &dummy);
        } else {
            Element *iter = l->head;
            int i = 0;
            
            do{
                if(i == j) {
                    if(iter == l->tail) {
                        int dum;
                        deleteTail(l, &dum);
                    } else {
                        iter->next->prev = iter->prev;
                        iter->prev->next = iter->next;

                        free(iter);
                    }

                    break;
                }

                i++;
                iter = iter->next;
            } while(iter != l->head);
        }
    } 
}

void showListFromHead(List *l)
{
    Element *iter = l->head;
    
    if(iter == NULL) {
        printf("\n");
        return;
    }
    
    do {
        printf("%d,", iter->data);
        iter = iter->next;
    } while(iter != l->head);

    printf("\n");
}

void showListFromTail(List *l)
{
    Element *iter = l->tail;
    
    if(iter == NULL) {
        printf("\n");
        return;
    }

    do { 
        printf("%d,", iter->data);
        iter = iter->prev;
    } while(iter != l->tail);

    printf("\n");
}


void clearList(List *l)
{
    Element *iter = l->head;
    
    if(iter == NULL) {
        return;
    }

    do {
        Element *temp = iter->next;
        free(iter);
        iter = NULL;
        iter = temp;
    } while(iter != l->head);

    l->tail = NULL;
    l->head = NULL;
}

void addList(List *one, List *two)
{
    if(two->head == NULL || one->head == NULL) {
        return;
    }

    one->tail->next = two->head;
    two->head->prev = one->tail;

    two->tail->next = one->head;
    one->tail = two->tail;
    one->head->prev = one->tail;

    two->head = two->tail = NULL;
}

void showBool(int bool) {
    printf("%s\n", bool ? "true" : "false");
}

int main(int argc, char const *argv[]) {
    char line[256];
    char *p;

    List *list;

    int currentL = 0;
    int value;

    printf("START\n");

    while(1) {
        fgets(line, sizeof(line) - 1, stdin);

        if(line[0] == '#' || line[0] == '\n') {
            continue;
        }

        printf("!%s", line);

        p = strtok(line, " \n");

        p[0] = toupper(p[0]);
        p[1] = toupper(p[1]);

        if(strcmp(p, "HA") == 0) {
            printf("END OF EXECUTION\n");
            break;
        }

        if(strcmp(p, "DH") == 0) {
			int value;
            int ret = deleteHead(&list[currentL], &value);

			if(ret)
				printf("%d\n", value);
			else
				showBool(ret);

			continue;
		}

        if(strcmp(p, "DT") == 0) {
            int value;
			int ret = deleteTail(&list[currentL], &value);

			if(ret)
				printf("%d\n", value);
			else
				showBool(ret);

			continue;
		}

        if(strcmp(p, "SH") == 0) {
            showListFromHead(&list[currentL]);
            continue;
        }

        if(strcmp(p, "ST") == 0) {
            showListFromTail(&list[currentL]);
            continue;
        }

        if(strcmp(p, "CL") == 0) {
			clearList(&list[currentL]);
			continue;
		}

        if(strcmp(p, "IN") == 0) {
			init(&list[currentL]);
			continue;
		}

        if(strcmp(p, "FV") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

			int ret = findValue(&list[currentL], value);

			printf("%d\n", ret);

			continue;
		}

        if(strcmp(p, "RV") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

			removeAllValue(&list[currentL], value);

			continue;
		}

        if(strcmp(p, "CH") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

			currentL = value;

			continue;
		}

        if(strcmp(p, "IH") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

			insertHead(&list[currentL], value);
		
            continue;
		}

        if(strcmp(p, "AD") == 0){
            p = strtok(NULL, " ");

            value = atoi(p);
            
            if(currentL != value)
                addList(&list[currentL], &list[value]);

            continue;
        }

		if(strcmp(p, "IT") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

			insertTail(&list[currentL], value);
			continue;
		}

        if(strcmp(p, "GO") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

            list = malloc(value * sizeof(List));

            continue;
        }

        printf("wrong argument in test: %s\n", line);
    }

    free(list);

    return 0;
}
