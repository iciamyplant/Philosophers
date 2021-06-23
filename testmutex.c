#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
pthread_mutex_t lock;

void *myThreadFun2(void *vargp)
{
	sleep(1);
	printf("test 2\n");
	return (NULL);
}

void *myThreadFun(void *vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

int main()
{
    pthread_t thread_id;
	pthread_t thread_id2;
    printf("Before Thread\n");
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    //pthread_join(thread_id, NULL);
    pthread_create(&thread_id2, NULL, myThreadFun, NULL);
    //pthread_join(thread_id2, NULL);
    printf("After Thread\n");
    exit(0);
}