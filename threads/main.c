#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#include <mysql.h>

#include "threadpool.h"
#include "mysql_helper.h"

#define THREAD 1
#define SIZE   256

threadpool_t *pool;
int tasks = 0;
pthread_mutex_t lock;

int error;

void dummy_task(void *arg) {
    usleep(100);
    int tid = (int) (intptr_t)arg;

    struct connections *ss;

    HASH_FIND_INT(m_con_arr, &tid, ss);

    pthread_mutex_lock(&lock);
    char buff[255] = {0};
    snprintf(buff, 254, "Thread #%d working", tid);
    char buf[255] = {0};
    snprintf(buf, 254, "INSERT INTO test (title) VALUES('%s')", buff);
    if (mysql_query(ss->conn, buf)) {
        fprintf(stderr, "%s\n", mysql_error(ss->conn));
        exit(1);
    }
    printf( "Thread #%d inserted row!, Remaining Tasks: %d\n", tid, tasks);
    tasks--;
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv)
{
    int i = 0,
        err;

    pthread_mutex_init(&lock, NULL);
    
    if((pool = threadpool_create(THREAD, SIZE, 0)) == NULL) {
      fprintf(stderr, "Pool is NULL!");
      return 1;
    }
    while((err = threadpool_add(pool, &dummy_task, (void*) (intptr_t)i, 0)) == 0) {
        pthread_mutex_lock(&lock);
        tasks++;
        pthread_mutex_unlock(&lock);
        i++;
    }

    printf("%d tasks created\n", tasks);

    while(tasks > 0) {
      usleep(100);
    }
    
    assert(threadpool_destroy(pool, 0) == 0);
    pthread_mutex_destroy(&lock);

    return 0;
}
