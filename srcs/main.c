#include "../include/philo.h"

int		ft_exit(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

void	stop(t_p *p)
{
	int	i;

	i = -1;
	while (!p->a.stop)
		ft_usleep(1);
	while (++i < p->a.total)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->a.write_mutex);
	i = -1;
	while (++i < p->a.total)	
		pthread_mutex_destroy(&p->ph[i].l_f);
	if (p->a.stop == 2)
		printf("Each philosopher ate %d time(s)\n", p->a.m_eat);
	free(p->ph);
}

int		main(int argc, char **argv)
{
	t_p		p;

	if (!(parse_args(argc, argv, &p)))
		return (ft_exit("Invalid Arguments\n"));
	if (!(p.ph = (malloc(sizeof(t_philo) * p.a.total))))
		return (ft_exit("Malloc returned NULL\n"));
	if (!initialize(&p) || !threading(&p))
	{
		free(p.ph);
		return (0);
	}
	stop(&p);
}