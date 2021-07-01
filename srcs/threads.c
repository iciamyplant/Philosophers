#include "../include/philo.h"

void	*is_dead(void	*data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	while (!ph->pa->stop)
	{
		if ((ph->ms_eat == 0 && ((actual_time() - ph->pa->start_t) >= (long)(ph->pa->die)))
			|| (ph->ms_eat && ((actual_time() - ph->ms_eat) >= (long)(ph->pa->die)))) // quand le philosophe n'a encore jamais mange
		{
			pthread_mutex_lock(&ph->pa->write_mutex);
			write_status("died\n", ph);
			ph->pa->stop = 1;
			ft_usleep(100);
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
		ft_usleep(ph->pa->die);
		//ft_usleep(ph->pa->die / 10);
	}
	return NULL;
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

int		threading(t_p *p)
{
	int i;

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