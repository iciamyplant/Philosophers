#include "philo.h"

int     ft_exit(char *str)
{
    printf("%s\n", str);
    return (-1);
}

int    initialize(t_p *p)
{
    struct timeval current_time;
    int i;

    i = 0;
    if (gettimeofday(&current_time, NULL) == -1)
        return (0);
    p->s = current_time.tv_sec;
    p->ms = current_time.tv_usec;
    while (i < p->a.total)
    {
        p->ph[i].id = i;
        //pthread_mutex_init(p->ph[i].l_f, NULL);
        i++;
    }
    return (1);
}