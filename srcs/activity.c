#include "../include/philo.h"

void	*is_dead(void	*data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	while (!ph->pa->stop)
	{
		if (ph->ms_eat == 0 && ((actual_time() - ph->pa->start_t) >= (long)(ph->pa->die))) // quand le philosophe n'a encore jamais mange
		{
			ph->pa->stop = 1;
			return NULL;
		}
		if (ph->ms_eat && ((actual_time() - ph->ms_eat) >= (long)(ph->pa->die)))
		{
			ph->pa->stop = 1;
			return NULL;
		}
		if (ph->nb_eat == ph->pa->m_eat)
			ph->pa->stop = 2;
	}
	return NULL;
}

void	sleeping_thinking(t_philo *ph)
{
	write_status(" is sleeping\n", ph);
	usleep(ph->pa->sleep * 1000);
	write_status(" is thinking\n", ph);
}

void	activity(t_philo *ph)
{
	if (ph->id % 2 != 0)
	{
		if (ph->id != ph->r_fid)
			pthread_mutex_lock(ph->r_f);
	}
	if (ph->id % 2 == 0)
	{
		if (ph->id != ph->l_fid)
			pthread_mutex_lock(&ph->l_f);
	}
	if (ph->id % 2 != 0)
	{
		if (ph->id != ph->l_fid)
			pthread_mutex_lock(&ph->l_f);
	}
	if (ph->id % 2 == 0)
	{
		if (ph->id != ph->r_fid)
			pthread_mutex_lock(ph->r_f);
	}
	write_status(" has taken a fork\n", ph);
	write_status(" is eating\n", ph);
	usleep(ph->pa->eat * 1000);
	pthread_mutex_unlock(ph->r_f);
	pthread_mutex_unlock(&ph->l_f);
	ph->r_fid = ph->id;
	ph->l_fid = ph->id;
	ph->nb_eat++;
	ph->ms_eat = actual_time();
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
	if (ph->pa->stop == 2)
		write_status(" EATEN ENOUGH\n", ph);
	else if (ph->pa->stop == 1)
		write_status(" DIED\n", ph);
	return NULL;
}