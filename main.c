#include "philo.h"

void    initialize(t_p *p)
{
    struct timeval current_time;
    int i;

    i = 0;
    gettimeofday(&current_time, NULL);
    p->s = current_time.tv_sec;
    p->ms = current_time.tv_usec;
    printf("seconds : %ld\nmicro seconds : %d", current_time.tv_sec, current_time.tv_usec);
    while (i < p->a.total)
    {
        p->ph[i].id = i;
        i++;
    }
}
void    *myThreadFun(void *vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

void    threading(t_p *p)
{
    printf("Before Thread\n");
    pthread_create(&p->ph[0].thread_id, NULL, myThreadFun, NULL);
    pthread_join(p->ph[0].thread_id, NULL); 
    printf("After Thread\n");
}

int     main(int argc, char **argv)
{
    t_p         p;

    if (!(parse_args(argc, argv, &p)))
        printf("Invalid Arguments\n");
    if (!(p.ph = (malloc(sizeof(t_philo) * p.a.total))))
        printf("Malloc error\n");
    initialize(&p);
    threading(&p);
}