#include "../include/philo.h"

void	*is_dead(void	*data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	while (!ph->pa->stop)
	{
		usleep(ph->pa->die / 100);
		if ((ph->ms_eat == 0 && ((actual_time() - ph->pa->start_t) >= (long)(ph->pa->die)))
			|| (ph->ms_eat && ((actual_time() - ph->ms_eat) >= (long)(ph->pa->die)))) // quand le philosophe n'a encore jamais mange
		{
			pthread_mutex_lock(&ph->pa->write_mutex);
			write_status("died\n", ph);
			ph->pa->stop = 1;
			pthread_mutex_unlock(&ph->pa->write_mutex);
			return NULL;
		}
		if (ph->nb_eat == ph->pa->m_eat)
		{
			pthread_mutex_lock(&ph->pa->write_mutex);
			ph->pa->nb_p_finish++;
			write_status("ate enough\n", ph);
			if (ph->pa->nb_p_finish == ph->pa->total)
				ph->pa->stop = 2;
			pthread_mutex_unlock(&ph->pa->write_mutex);
		}
	}
	return NULL;
}

void	activity(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	pthread_mutex_lock(ph->r_f);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("has taken a fork\n", ph);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);

	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is eating\n", ph);
	ph->ms_eat = actual_time();
	pthread_mutex_unlock(&ph->pa->write_mutex);
	ft_usleep(ph->pa->eat);
	pthread_mutex_unlock(ph->r_f);
	pthread_mutex_unlock(&ph->l_f);
	ph->nb_eat++;

	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	ft_usleep(ph->pa->sleep);

	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is thinking\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
}

void	*thread(void *data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	if (pthread_create(&ph->thread_death_id, NULL, is_dead, data) != 0)
		ft_exit("Pthread did not return 0\n");
	if (ph->id % 2 == 0)
        ft_usleep(ph->pa->eat);
	while (!ph->pa->stop)
		activity(ph);
	return (NULL);
}