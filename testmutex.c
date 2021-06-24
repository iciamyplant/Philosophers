#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
pthread_mutex_t lock;
pthread_t tid[2];

char arr[10];
int test = 0;

void *myThreadFun(void *vargp)
{
    sleep(1);
    int j;
    pthread_t id = pthread_self();

    printf("hello world\n");
    printf("goodbye hell\n");
    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
    }
    else
    {
        printf("\n Second thread processing\n");
    }
    if (test == 0)
    {
        printf("\n No storage\n");
        return NULL;
    }
    test = 8;
    printf("index = %d\n", test);
    for(j=0; j<(0xFFFFFFFF);j++);
    return NULL;
}

int main()
{
    printf("Before Thread\n");
    //pthread_mutex_init(&lock, NULL);
    pthread_create(&(tid[0]), NULL, myThreadFun, NULL);
    pthread_create(&(tid[1]), NULL, myThreadFun, NULL);
    //pthread_join((tid[0]), NULL);
    //pthread_join((tid[1]), NULL);
    sleep(5);
    printf("After Thread\n");
    exit(0);
}