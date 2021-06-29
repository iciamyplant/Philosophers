#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef	struct              s_p
{
    pthread_mutex_t         mutex;
    int                     i;
}                           t_p;

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    *go1(void *pp)
{
    char *str;
    str = "tread 1 : coucou ca va ? \n";
    int i = 0;
    t_p *ppp;

    ppp = (t_p *)pp;

    //printf("i = %d\n", ppp->i);
    //pthread_mutex_lock(&ppp->mutex);
    printf("retour 2 = %d\n", pthread_mutex_trylock(&ppp->mutex));
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    //pthread_mutex_unlock(&ppp->mutex);
    return (NULL);
}

int main()
{
    pthread_t               thread_id1;
    pthread_t               thread_id2;
    t_p                     p;
    t_p                     *pp;

    pp = (malloc(sizeof(t_p) * 1));
    pp = &p;
    p.i = 3;
    int retour;
    retour = -1;

    pthread_mutex_init(&p.mutex, NULL);
    //pthread_mutex_lock(&p.mutex);
    retour = pthread_mutex_trylock(&p.mutex);
    printf("retour = %d\n", retour);
    pthread_create(&thread_id1, NULL, go1, (void *)pp);
    pthread_create(&thread_id2, NULL, go1, (void *)pp);
    sleep(1);
}

    // printf("----------philo %d STARTS eating at : %ld\n", ph->id, actual_time() - ph->pa->start_t);
    // printf("----------philo %d STOPS eating at : %ld\n", ph->id, actual_time() - ph->pa->start_t);