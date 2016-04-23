#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

char *Read(FILE *f)
{
    char *line = malloc(127);
    
    if(fgets(line, 127, f) != NULL) {
        size_t ln = strlen(line) - 1;
        if (line[ln] == '\n')
            line[ln] = '\0';
        if (line[ln - 1] == '\r')
            line[ln - 1] = '\0';
        return line;
    }
    return NULL;
}

typedef struct _student {
    int id;
    char *nm;
    char *uni;
    int fs[256];
    int bs[256];
} student;

student *ss[256];
int sc = 0;

student *get(char *s)
{
    int i;
    for(i=0;i<256;i++) {
        student *t = ss[i];
        if(t && strcmp(t->nm, s)==0)
            return t;
    }
    return NULL;
}

void add(char *rc)
{
    char n[36]; int a; char u[36];
    sscanf(rc, "%35[^,],%d,%35[^\n]", n, &a, u);
    char *nn = malloc(37);
    strcpy(nn, n);
    char *uu = malloc(37);
    strcpy(uu, u);
    student *s = malloc(sizeof(student));
    s->id = sc;
    s->nm = nn;
    s->uni = uu;
    memset(s->fs, 0, 256);
    memset(s->bs, 0, 256);
    ss[sc] = s;
    sc++;
}

void friend(char *rc) {
    char i[36], k[36];
    sscanf(rc, "%[^,],%[^\n]", i, k);
    if(strcmp(i, k)==0) {
        printf("You cannot add yourself as your friend\n");
        return;
    }
    student *ii = get(i);
    student *kk = get(k);
    if(ii->fs[kk->id]) {
        printf("%s has already been friends with %s\n", i, k);
        return;
    }

    ii->fs[kk->id] = kk->fs[ii->id] = 1;
    printf("%s is now friends with %s\n", i, k);
}

void rfriend(char *rc) {
    char i[36], k[36];
    sscanf(rc, "%[^,],%[^\n]", i, k);
    
    student *ii = get(i);
    student *kk = get(k);
    if(!ii->fs[kk->id]) {
        printf("%s and %s have not been friends\n", i, k);
        return;
    }

    ii->fs[kk->id] = kk->fs[ii->id] = 0;
    printf("%s and %s are not friend anymore\n", i, k);
}

void block(char *rc) {
    char i[36], k[36];
    sscanf(rc, "%[^,],%[^\n]", i, k);
    student *ii = get(i);
    student *kk = get(k);
    if(ii->bs[kk->id]) {
        printf("%s has already blocked %s\n", i, k);
        return;
    }

    ii->bs[kk->id] = 1;
    printf("%s blocked %s\n", i, k);
}

void ublock(char *rc) {
    char i[36], k[36];
    sscanf(rc, "%[^,],%[^\n]", i, k);
    student *ii = get(i);
    student *kk = get(k);
    if(!ii->bs[kk->id]) {
        printf("%s has already unblocked %s\n", i, k);
        return;
    }

    ii->bs[kk->id] = 1;
    printf("%s unblocked %s\n", i, k);
}

void listu(char *rc) {
    student *ii = get(rc);

    printf("%s's friends with same universtiy:\n", rc);

    int i;
    for(i = 0;i<256;i++) {
        if(ii->fs[i] && !ii->bs[i]) {
            student *o = ss[i];
            if(strcmp(ii->uni, o->uni) == 0) {
                printf("\t%s\n", o->nm);
            }
        }
    }
}

void listc(char *rc) {
    char j[36], k[36];
    sscanf(rc, "%[^,],%[^\n]", j, k);
    student *jj = get(j);
    student *kk = get(k);
    printf("%s and %s have these common friends:\n", j, k);

    int i;
    for(i = 0;i<256;i++) {
        if(jj->fs[i] && !jj->bs[i]) {
            if(kk->fs[i] && !kk->bs[i]) {
                student *o = ss[i];
                printf("\t%s\n", o->nm);
            }
        }
    }
}

void message(char *rc) {
    char j[36], k[36], m[36];
    sscanf(rc, "%[^,],%[^,],%[^\n]", j, k, m);
    student *jj = get(j);
    student *kk = get(k);
    
    if(kk->bs[jj->id]) {
        printf("Message can not be sent. %s has already blocked %s!\n", k, j);
        return;
    }

    printf("%s sent %s a message: %s\n", j, k, m);
}

void lista(char *rc) {
    student *ii = get(rc);

    printf("%s's all friends:\n", rc);

    int i;
    for(i = 0;i<256;i++) {
        if(ii->fs[i] && !ii->bs[i]) {
            student *o = ss[i];
            printf("\t%s\n", o->nm);
        }
    }
}

int main()
{
    FILE *cmf = fopen("commands.txt", "r");
    char *l;
    while((l = Read(cmf)) != NULL) {
        char c;
        char rc[256];
        sscanf(l, "%c %255[^\n]", &c, rc);
        if(c == 'P') {
            add(rc);
        } else if(c == 'F') {
            friend(rc);
        } else if(c == 'R') {
            rfriend(rc);
        } else if(c == 'B') {
            block(rc);
        } else if(c == 'U') {
            ublock(rc);
        } else if(c == 'S') {
            listu(rc);
        } else if(c == 'A') {
            lista(rc);
        } else if(c == 'C') {
            listc(rc);
        } else if(c == 'M') {
            message(rc);
        }

    }
    return 0;
}