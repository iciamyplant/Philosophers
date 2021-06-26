#include "../include/philo.h"

int    is_died(t_philo *ph)
{
    struct timeval      current_time;
    int                 now;

    gettimeofday(&current_time, NULL);
    now = current_time.tv_usec;
    if (ph->ms_eat == 0) // quand le philosophe n'a encore jamais mange
        if ((ph->pa->start_t - actual_time()) >= (ph->pa->die * 1000))
            return (1);
    if (ph->ms_eat)
        if ((ph->ms_eat - actual_time()) >= (ph->pa->die * 1000))
            return (1);
    return (0);
}

void    sleeping_thinking(t_philo *ph)
{
    usleep(ph->pa->sleep * 1000); // is sleeping
    write_status(" is sleeping\n", ph);
    write_status(" is thinking\n", ph);
}

void    activity(t_philo *ph)
{
    if (ph->id % 2 == 0 && ph->id != ph->r_fid)
        pthread_mutex_lock(&ph->r_f);
    else
        pthread_mutex_lock(&ph->l_f);
    if (ph->id % 2 == 0 && ph->id != ph->l_fid)
        pthread_mutex_lock(&ph->l_f);
    else
        pthread_mutex_lock(&ph->r_f);
    write_status(" take fork\n", ph);
    usleep(ph->pa->eat * 1000); //is eating
    write_status(" is eating\n", ph);
    ph->r_fid = ph->id;
    ph->l_fid = ph->id;
    ph->nb_eat++;
    ph->ms_eat = actual_time();
    pthread_mutex_unlock(&ph->r_f);
    pthread_mutex_unlock(&ph->l_f);
    sleeping_thinking(ph);
}

void    *myThreadFun(void *data)
{
    t_philo *ph;

    ph = (t_philo *)data;
    ph->ms_eat = 0;
    ph->nb_eat = 0;
    while (!is_died(ph))
    {
        if (ph->nb_eat == ph->pa->m_eat)
        {
            write_status(" ate enough\n", ph);
            return NULL;
        }
        activity(ph);   
    }
    write_status(" died\n", ph);
    return NULL;
}