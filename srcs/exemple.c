#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
typedef	struct              s_p
{
    pthread_mutex_t         mutex;
    int                     lol;
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

    //pthread_mutex_lock(&ppp->mutex);
    ppp->lol++;
    //pthread_mutex_lock(&ppp->mutex);
    pthread_mutex_lock(&ppp->mutex);
    while (str[i] && ppp->lol > 0)
    {
        write(1, &str[i], 1);
        i++;
    }
    pthread_mutex_unlock(&ppp->mutex);
    return (NULL);
}

int main()
{
    pthread_t               thread_id1;
    pthread_t               thread_id2;
    t_p                     p;
    t_p                     *pp;

    pp = (malloc(sizeof(t_p) * 2));
    pp[0].lol = 2;
    pp[1].lol = 2;

    pthread_mutex_init(&p.mutex, NULL);
    pthread_create(&thread_id1, NULL, go1, &pp[0]);
    pthread_create(&thread_id2, NULL, go1, &pp[1]);
    sleep(1);
}