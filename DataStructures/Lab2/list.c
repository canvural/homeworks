#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _el{
    int data;
    struct _el *next;
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

    el->next = l->head;
    l->head = el;

    if(l->tail == NULL) {
        l->tail = el;
    }
}

int deleteHead(List *l){
    if(l->head == NULL) {
        return -1;
    }

    Element *old = l->head;

    int ret = old->data;

    l->head = old->next;

    free(old);

    return ret;
}

void insertTail(List *l, int x)
{
    Element *el = malloc(sizeof(Element));

    el->data = x;
    el->next = NULL;

    l->tail->next = el;
    l->tail = el;
}

int deleteTail(List *l)
{
    if(l->head == NULL) {
        return -1;
    }

    Element *old = l->tail;

    int ret = old->data;

    Element *iter = l->head;
    while(iter->next != l->tail) {
        iter = iter->next;
    }

    l->tail = iter;
    iter->next = NULL;

    free(old);

    return ret;
}

int findPosOfValue(List *l, int value)
{
    Element *iter = l->head;
    int i = 0;

    while(iter != NULL) {
        if(iter->data == value) {
            return i;
        }

        iter = iter->next;
        i++;
    }

	return -1;
}

int deleteValue(List *l, int value)
{
    Element *iter = l->head;
    Element *prev = NULL;

    while(iter != NULL) {
        if(iter->data == value) {
            if(prev == NULL) {
                return deleteHead(l);
            } else if(iter == l->tail) {
                return deleteTail(l);
            }

            prev->next = iter->next;
            free(iter);

            return 1;
        }

        prev = iter;
        iter = iter->next;
    }

	return -1;
}

int atPosition(List *l, int pos)
{
    Element *iter = l->head;
    int i = 0;

    while(iter != NULL) {
        if(i == pos) {
            return iter->data;
        }

        iter = iter->next;
        i++;
    }

	return -1;
}

void showListFromHead(List *l)
{
    Element *iter = l->head;

    while(iter != NULL) {
        printf("%d,", iter->data);
        iter = iter->next;
    }

    printf("\n");
}

void clearList(List *l)
{
    Element *iter = l->head;

    while(iter != NULL) {
        Element *temp = iter->next;
        free(iter);
        iter = temp;
    }

    l->head = l->tail = NULL;

    free(l);
}

void showBool(int bool) {
    printf("%s\n", bool != -1 ? "true" : "false");
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

        if(strcmp(p,  "DH") == 0) {
			int ret = deleteHead(&list[currentL]);

			if(ret != -1)
				printf("%d\n", ret);
			else
				showBool(ret);

			continue;
		}

        if(strcmp(p, "DT") == 0) {
			int ret = deleteTail(&list[currentL]);

			if(ret != -1)
				printf("%d\n", ret);
			else
				showBool(ret);

			continue;
		}

        if(strcmp(p, "SH") == 0) {
            showListFromHead(&list[currentL]);
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

        if(strcmp(p, "FP") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

			int ret = findPosOfValue(&list[currentL], value);

			printf("%d\n", ret);

			continue;
		}

        if(strcmp(p, "AT") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

			int retValue = atPosition(&list[currentL], value);

			if(retValue != -1)
				printf("%d\n", retValue);
			else
				showBool(retValue);

			continue;
		}

        if(strcmp(p, "DV") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

			showBool(deleteValue(&list[currentL], value));

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

    return 0;
}
