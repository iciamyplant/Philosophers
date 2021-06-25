#include "../include/philo.h"

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
    p->a.s = current_time.tv_sec;
    p->a.ms = current_time.tv_usec;
    while (i < p->a.total)
    {
        p->ph[i].id = i;
        if (i == p->a.total - 1)
            p->ph[i].r_f = p->ph[0].l_f;
        else
            p->ph[i].r_f = p->ph[i + 1].l_f; // chaque philosopher detient sa fourchette a gauche et emprunte celle de son voisin de droite
        //pthread_mutex_init(p->ph[i].l_f, NULL);
        i++;
    }
    return (1);
}