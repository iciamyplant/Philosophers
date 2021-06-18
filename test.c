#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void	*func1(void *arg)
{
	int i = 0;

	while (i < 10)
	{
		printf("test %d\n", i);
	}
	pthread_exit(NULL);
}

void	*func2(void *arg)
{
	int i = 0;

	while (i < 10)
	{
		printf("test 2 %d\n", i);
	}
	pthread_exit(NULL);
}

int		main()
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1, NULL, func1, NULL); // 3 threads vont fonctionner en meme temps, le main est un thread a part entiere
	pthread_create(&t2, NULL, func2, NULL);

}
