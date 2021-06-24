#include "philo.h"

void    sleeping(t_philo *ph)
{
    usleep(ph->pa->sleep * 1000); // is sleeping
    printf("Philo %d is sleeping\n", ph->id);
    printf("Philo %d is thinking\n", ph->id);
}

void    eating(t_philo *ph)
{
    if (ph->id % 2 == 0 && ph->id != ph->r_fid)
        pthread_mutex_lock(&ph->r_f);
    else
        pthread_mutex_lock(&ph->l_f);
    if (ph->id % 2 == 0 && ph->id != ph->l_fid)
        pthread_mutex_lock(&ph->l_f);
    else
        pthread_mutex_lock(&ph->r_f);
    printf("Philo %d has taken forks\n", ph->id);
    usleep(ph->pa->eat * 1000); //is eating
    printf("Philo %d is eating\n", ph->id);
    ph->r_fid = ph->id;
    ph->l_fid = ph->id;
    pthread_mutex_unlock(&ph->r_f);
    pthread_mutex_unlock(&ph->l_f);
    sleeping(ph);
}