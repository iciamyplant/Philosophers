#include "../include/philo.h"

void	*is_dead(void	*data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	while (!ph->pa->stop)
	{
		if (ph->ms_eat == 0) // quand le philosophe n'a encore jamais mange
		{
			//printf("- - - - - - - - - actual time - ph->pa->start_t = %ld\n", actual_time() - ph->pa->start_t);
			if ((actual_time() - ph->pa->start_t) >= (long)(ph->pa->die))
			{
				ph->pa->stop = 1;
				return NULL;
			}
		}
		// printf("ph->nb_eat = %d\n", ph->nb_eat);
		if (ph->ms_eat)
		{
			if ((actual_time() - ph->ms_eat) >= (long)(ph->pa->die))
			{
				printf("actual time - ph->ms_eat = ||| %ld ||| for philo %d \n", actual_time() - ph->ms_eat, ph->id);
				ph->pa->stop = 1;
				return NULL;
			}
		}
		if (ph->nb_eat == ph->pa->m_eat)
		{
			ph->pa->stop = 2;
			write_status(" ate enough\n", ph);
			return NULL;
		}
	}
	//printf("now = %d\n", now);
	//printf("ph->ms_eat = %ld\n", ph->ms_eat);
	return NULL;
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
	t_philo					*ph;
	pthread_t				thread_death_id;

	pthread_create(&thread_death_id, NULL, is_dead, data);
	ph = (t_philo *)data;
	while (!ph->pa->stop)
        activity(ph);
    write_status(" died\n", ph);
    return NULL;
}