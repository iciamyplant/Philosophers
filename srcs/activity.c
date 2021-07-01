#include "../include/philo.h"

void			write_status(char *str, t_philo *ph)
{
	//pthread_mutex_lock(&ph->pa->write_mutex);
	printf("%ld ", (actual_time() - ph->pa->start_t));
	printf("Philo %d %s", ph->id, str);
	//pthread_mutex_unlock(&ph->pa->write_mutex);
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