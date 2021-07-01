#include "../include/philo.h"

void	*is_dead(void	*data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
    ft_usleep(ph->pa->die + 1);
    //pthread_mutex_lock(&ph->pa->write_mutex);
    //ft_putstr_fd("DEATH CHECK for philo", 1);
    //ft_putnbr_fd((long)ph->id, 1);
    //printf("ou actual_time() - ph->ms_eat = %ld\n", actual_time() - ph->ms_eat);
    //pthread_mutex_unlock(&ph->pa->write_mutex);
    if ((actual_time() - ph->ms_eat) >= (long)(ph->pa->die))
    {
        pthread_mutex_lock(&ph->pa->write_mutex);
		write_status("died\n", ph);
		ph->pa->stop = 1;
		ft_usleep(100);
		//pthread_mutex_unlock(&ph->pa->write_mutex);  
    }
	return NULL;
}

void	*thread(void *data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
        ft_usleep(ph->pa->eat * 1000); // ?? avec ft_usleep(ph->pa->eat); marchait pas
	while (!ph->pa->stop && ph->nb_eat != ph->pa->m_eat)
    {
        pthread_create(&ph->thread_death_id, NULL, is_dead, data);
        activity(ph); // eat, sleep and think 1 time
        //ph->nb_eat++;
        pthread_detach(ph->thread_death_id);
    }
    //if (ph->nb_eat == ph->pa->m_eat)
   // {
//		pthread_mutex_lock(&ph->pa->write_mutex);
//		ph->pa->nb_p_finish++;
//		write_status("ate enough\n", ph);
//		if (ph->pa->nb_p_finish == ph->pa->total)
//			ph->pa->stop = 2;
//		pthread_mutex_unlock(&ph->pa->write_mutex);
//    }
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