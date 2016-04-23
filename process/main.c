#include <stdio.h>   /* printf, stderr, fprintf */
#include <sys/types.h> /* pid_t */
#include <unistd.h>  /* _exit, fork */
#include <stdlib.h>  /* exit */
#include <errno.h>   /* errno */
#include <pthread.h>

char *input_folder;

void project();

int main(int argc, char **argv)
{
	if(argc < 2) {
		return 1;
	}

	input_folder = argv[1];

	pid_t  project_pid,
		   midterm_pid,
		   final_pid;

	pthread_mutex_t pmutex;
	pthread_mutexattr_t attrmutex;

	/* Initialise attribute to mutex. */
	pthread_mutexattr_init(&attrmutex);
	pthread_mutexattr_setpshared(&attrmutex, PTHREAD_PROCESS_SHARED);

	pthread_mutex_init(&pmutex, &attrmutex);

   	project_pid = fork();

   	// Project process
   	if (project_pid == -1) {
    	fprintf(stderr, "can't fork, error %d\n", errno);
    	exit(EXIT_FAILURE);
    } else if (project_pid == 0) {
    	project();
    } else {
    	midterm_pid = fork();

	   	// Project process
	   	if (midterm_pid == -1) {
	    	fprintf(stderr, "can't fork, error %d\n", errno);
	    	exit(EXIT_FAILURE);
	    } else if (midterm_pid == 0) {
	    	pthread_mutex_lock(&pmutex);
	    	printf("Hello from midterm %d", getpid());
	    	pthread_mutex_unlock(&pmutex);
	    } else {
	    	final_pid = fork();

		   	// Project process
		   	if (final_pid == -1) {
		    	fprintf(stderr, "can't fork, error %d\n", errno);
		    	exit(EXIT_FAILURE);
		    } else if (final_pid == 0) {
		    	pthread_mutex_lock(&pmutex);
		    	printf("Hello from final %d", getpid());
		    	pthread_mutex_unlock(&pmutex);
		    }
	    }
    }

    pthread_mutex_destroy(&pmutex);
	pthread_mutexattr_destroy(&attrmutex); 
}

void project()
{

}