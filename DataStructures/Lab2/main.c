#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _queue{
    int size;
    int *arr;
    int index;
} Queue;

void init(Queue *q, int size) {
    q->size = size;
    q->arr = malloc(size * sizeof(int));
    q->index = 0;
}

int enqueue(Queue *q, int value) {
    if(isFull(q)) {
        return 0;
    }

    q->arr[q->index++] = value;

    return 1;
}

int dequeue(Queue *q) {
    if(isEmpty(q)) {
        return -1;
    }

    int ret = q->arr[0];

    // Shift the others
    int i;
    for(i = 1; i < q->index; i++) {
        q->arr[i - 1] = q->arr[i];
    }

    q->index--;

    return ret;
}

int isEmpty(Queue *q) {
    return q->index == 0;
}

int isFull(Queue *q) {
    return q->index == q->size;
}

void showBool(int bool) {
    printf("%s\n", bool ? "true" : "false");
}

void show(Queue *q) {
    int i;

    for(i = 0; i < q->index; i++) {
        printf("%d,", q->arr[i]);
    }

    printf("\n");
}

int main(int argc, char const *argv[]) {
    char line[256];
    char *p;

    Queue *queue;

    int currentQ = 0;
    int value;

    printf("START\n");

    while(1) {
        fgets(line, sizeof(line) - 1, stdin);

        if(line[0] == '#' || line[0] == '\n') {
            continue;
        }

        printf("!%s", line);

        p = strtok(line, " \n");

        p[0]=toupper(p[0]);
        p[1]=toupper(p[1]);

        if(strcmp(p, "HA") == 0) {
            printf("END OF EXECUTION\n");
            break;
        }

        // zero-argument command
        if(strcmp(p, "EM") == 0) {
            showBool(isEmpty(&queue[currentQ]));
            continue;
        }

        if(strcmp(p, "FU") == 0) {
            showBool(isFull(&queue[currentQ]));
            continue;
        }

        if(strcmp(p, "SH") == 0) {
            show(&queue[currentQ]);
            continue;
        }

        if(strcmp(p, "DE") == 0) {
            int ret = dequeue(&queue[currentQ]);
            if(ret == -1)
                printf("false\n");
            else
                printf("%d\n", ret);
            continue;
        }

        if(strcmp(p, "GO") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

            queue = malloc(value * sizeof(Queue));

            continue;
        }

        if(strcmp(p, "CH") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

            currentQ = value;

            continue;
        }

        if(strcmp(p, "IN") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

            init(&queue[currentQ], value);

            continue;
        }

        if(strcmp(p, "EN") == 0) {
            p = strtok(NULL, " ");

            value = atoi(p);

            int ret = enqueue(&queue[currentQ], value);
            showBool(ret);
            continue;
        }

        printf("wrong argument in test: %s\n", line);
    }

    return 0;
}
