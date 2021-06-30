#include "../include/philo.h"

int		ft_exit(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
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

void		stop(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->a.total)
	{
		pthread_detach(p->ph[i].thread_id);
		pthread_detach(p->ph[i].thread_death_id);
		i++;
	}
	if (p->a.stop == 2)
		printf("Each philosopher ate %d times\n", p->a.m_eat);
}

int		main(int argc, char **argv)
{
	t_p		p;

	if (!(parse_args(argc, argv, &p)))
		return (ft_exit("Invalid Arguments\n"));
	if (!(p.ph = (malloc(sizeof(t_philo) * p.a.total))))
		return (ft_exit("Malloc returned NULL\n"));
	if (!initialize(&p) || !threading(&p))
		return (0);
	while (!p.a.stop)
		ft_usleep(1);
	if (p.a.stop)
		stop(&p);
	return (0);
}