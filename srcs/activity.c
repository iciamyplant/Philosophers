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
			ph->pa->stop = 1;
			return NULL;
		}
		if (ph->nb_eat == ph->pa->m_eat)
			ph->pa->stop = 2;
	}
	return NULL;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	activity(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	pthread_mutex_lock(ph->r_f);
	pthread_mutex_lock(&mutex);
	write_status("has taken a fork\n", ph);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_lock(&mutex);
	write_status("is eating\n", ph);
	ph->ms_eat = actual_time();
	pthread_mutex_unlock(&mutex);
	ft_usleep(ph->pa->eat); //peut attendre un peu plus que ce que je rentre dans usleep
	pthread_mutex_unlock(ph->r_f);
	pthread_mutex_unlock(&ph->l_f);
	ph->nb_eat++;

	pthread_mutex_lock(&mutex);
	write_status("is sleeping\n", ph);
	pthread_mutex_unlock(&mutex);
	ft_usleep(ph->pa->sleep);

	pthread_mutex_lock(&mutex);
	write_status("is thinking\n", ph);
	pthread_mutex_unlock(&mutex);
}

void	*thread(void *data)
{
	t_philo					*ph;
	pthread_t				thread_death_id;

	pthread_create(&thread_death_id, NULL, is_dead, data);
	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
        usleep(ph->pa->eat / 10);
	while (!ph->pa->stop)
		activity(ph);
	if (ph->pa->stop == 2)
		write_status(" EATEN ENOUGH\n", ph);
	else if (ph->pa->stop == 1)
		write_status(" DIED\n", ph);
	return NULL;
}