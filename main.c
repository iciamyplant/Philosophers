#include "philo.h"

void    threading(t_p *p)
{
    int i;
    
    i = 0;
    printf("Before Thread\n");
    while (i < p->a.total)
    {
        p->ph[i].pa = &p->a;
        pthread_create(&p->ph[i].thread_id, NULL, myThreadFun, &p->ph[i]);
        //pthread_create(&p->ph[i].thread_id, NULL, myThreadFun, (void *)p);
        i++;
    }
    sleep(3);
    printf("After Thread\n");
}

int     main(int argc, char **argv)
{
    t_p         p;

    if (!(parse_args(argc, argv, &p)))
        return (ft_exit("Invalid Arguments"));
    if (!(p.ph = (malloc(sizeof(t_philo) * p.a.total))))
        return (ft_exit("Malloc error"));
    if (!(initialize(&p)))
        return (ft_exit("Gettimeofday error"));
    threading(&p);
    sleep(1);
}