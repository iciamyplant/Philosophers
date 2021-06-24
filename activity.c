#include "philo.h"

int    is_died(t_philo *ph)
{
    struct timeval      current_time;
    int                 now;

    gettimeofday(&current_time, NULL);
    now = current_time.tv_usec;
    if (ph->ms_eat == 0)
        if ((ph->pa->ms - now) >= (ph->pa->die * 1000))
            return (1);
    if (ph->ms_eat)
        if ((ph->ms_eat - now) >= (ph->pa->die * 1000))
            return (1);
    return (0);
}

void    sleeping_thinking(t_philo *ph)
{
    usleep(ph->pa->sleep * 1000); // is sleeping
    printf("Philo %d is sleeping\n", ph->id);
    printf("Philo %d is thinking\n", ph->id);
}

void    activity(t_philo *ph)
{
    struct timeval current_time;

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
    gettimeofday(&current_time, NULL);
    ph->ms_eat = current_time.tv_usec;
    pthread_mutex_unlock(&ph->r_f);
    pthread_mutex_unlock(&ph->l_f);
    sleeping_thinking(ph);
}

void    *myThreadFun(void *data)
{
    t_philo *ph;

    ph = (t_philo *)data;
    ph->ms_eat = 0;
    while (!is_died(ph))
        activity(ph);
    printf("Philo %d died\n", ph->id);
    return NULL;
}