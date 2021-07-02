#include "../include/philo.h"

void	*is_dead(void	*data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	ft_usleep(ph->pa->die + 1);
	if (!ph->pa->stop && !ph->finish && ((actual_time() - ph->ms_eat) >= (long)(ph->pa->die)))
	{
		pthread_mutex_lock(&ph->pa->write_mutex);
		write_status("died\n", ph);
		ph->pa->stop = 1;
		//ft_usleep(200);
		//pthread_mutex_unlock(&ph->pa->write_mutex);
	}
	return NULL;
}

void	*thread(void *data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->pa->eat / 10);
	while (!ph->pa->stop)
	{
		pthread_create(&ph->thread_death_id, NULL, is_dead, data);
		activity(ph); // eat, sleep and think 1 time
		pthread_detach(ph->thread_death_id);
		if ((int)++ph->nb_eat == ph->pa->m_eat)
		{
			ph->finish = 1;
			ph->pa->nb_p_finish++;
			if (ph->pa->nb_p_finish == ph->pa->total)
				ph->pa->stop = 2;
			break;
		}
		//printf("-------------------------------CA RENTRE pour philo %d ou ph->nb_eat = %d et ph->pa->m_eat = %d\n", ph->id, ph->nb_eat, ph->pa->m_eat);
	}
	return (NULL);
}

int		threading(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->a.total)
	{
		p->ph[i].pa = &p->a;
		if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
			return (ft_exit("Pthread did not return 0\n"));
		i++;
	}
	return (1);
}