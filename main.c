#include "philo.h"

int    initialize(t_p *p)
{
    struct timeval current_time;
    int i;

    i = 0;
    if (gettimeofday(&current_time, NULL) == -1)
        return (0);
    p->s = current_time.tv_sec;
    p->ms = current_time.tv_usec;
    printf("seconds : %ld\nmicro seconds : %d\n", current_time.tv_sec, current_time.tv_usec);
    while (i < p->a.total)
    {
        p->ph[i].id = i;
        i++;
    }
    return (1);
}
void    *myThreadFun(void *data)
{
    t_p *p;

    p = (t_p*)data;
    printf("microseconds : %d\n", p->ms);
    usleep(p->a.eat * 1000); //is eating
    printf("is eating\n");
    usleep(p->a.sleep * 1000); // is sleeping
    printf("is sleeping\n");
    // is thinking
    //printf("is thinking\n");
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

void    threading(t_p *p)
{
    printf("Before Thread\n");
    // creer autant de threads que de philosophes
    pthread_create(&p->ph[0].thread_id, NULL, myThreadFun, (void *)p);
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
    if (!(initialize(&p)))
        printf("Gettimeofday error\n");
    printf("total = %d\n", p.a.total);
    printf("die = %d\n", p.a.die);
    printf("eat = %d\n", p.a.eat);
    printf("sleep = %d\n", p.a.sleep);
    printf("m_eat = %d\n", p.a.m_eat);
    //threading(&p);
}