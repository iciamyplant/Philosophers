#include "philo.h"

void    sleeping(t_p *p)
{
    usleep(p->a.sleep * 1000); // is sleeping
    printf("is sleeping\n");
}

void    eating(t_p *p)
{
    //pthread_mutex_lock(&p->ph[].r_f);
    usleep(p->a.eat * 1000); //is eating
    printf("is eating\n");
    sleeping(p);
}