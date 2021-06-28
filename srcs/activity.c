#include "../include/philo.h"

int    is_dead(t_philo *ph)
{
    struct timeval      current_time;
    int                 now;

    gettimeofday(&current_time, NULL);
    now = current_time.tv_usec;
    if (ph->ms_eat == 0) // quand le philosophe n'a encore jamais mange
    {
        //printf("- - - - - - - - - actual time - ph->pa->start_t = %ld\n", actual_time() - ph->pa->start_t);
        if ((actual_time() - ph->pa->start_t) >= (long)(ph->pa->die))
            return (1);
    }
    if (ph->ms_eat)
    {
        //printf("actual time - ph->ms_eat = %ld\n", actual_time() - ph->ms_eat);
        if ((actual_time() - ph->ms_eat) >= (long)(ph->pa->die))
        {
            return (1);
        }
    }
    //printf("ph->ms_eat = %ld\n", ph->ms_eat);
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
    if (ph->id % 2 != 0)
    {
        pthread_mutex_lock(ph->r_f);
        pthread_mutex_lock(&ph->l_f);
    }
    else if (ph->id % 2 == 0)
    {
        pthread_mutex_lock(&ph->l_f);
        pthread_mutex_lock(ph->r_f);
    }
    write_status(" has taken forks\n", ph);
    // printf("----------philo %d STARTS eating at : %ld\n", ph->id, actual_time() - ph->pa->start_t);
    usleep(ph->pa->eat * 1000); //is eating
    write_status(" is eating\n", ph);
    // printf("----------philo %d STOPS eating at : %ld\n", ph->id, actual_time() - ph->pa->start_t);
    //ph->r_fid = ph->id;
    //ph->l_fid = ph->id;
    ph->nb_eat++;
    ph->ms_eat = actual_time();
    pthread_mutex_unlock(ph->r_f);
    pthread_mutex_unlock(&ph->l_f);
    sleeping_thinking(ph);
}

void	*thread(void *data)
{
	t_philo *ph;
	//pthread_t               thread_death_id;

	ph = (t_philo *)data;
    //pthread_create(&thread_death_id, NULL, is_dead, &ph);
    while (!is_dead(ph))
    {
        if (ph->nb_eat == ph->pa->m_eat)
        {
            write_status(" ate enough\n", ph);
            ph->pa->stop = 2;
            return NULL;
        }
        if (is_dead(ph))
            break;
        activity(ph);
    }
    write_status(" died\n", ph);
    ph->pa->stop = 1;
    return NULL;
}