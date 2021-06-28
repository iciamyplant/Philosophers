#include "../include/philo.h"

int		ft_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	return (sum);
}

int		numeric(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0); //il y a un caractere autre qu'un chiffre
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int		parse_args(int argc, char **argv, t_p *p)
{
	if ((argc == 5 || argc == 6) && numeric(argv, 0, 1))
	{
		p->a.total = ft_atoi(argv[1]);
		if (p->a.total <= 1)
			return (0);
		p->a.die = ft_atoi(argv[2]);
		p->a.eat = ft_atoi(argv[3]);
		p->a.sleep = ft_atoi(argv[4]);
		p->a.m_eat = -1;
		if (argc == 6)
			p->a.m_eat = ft_atoi(argv[5]);
		return (1);
	}
	return (0);
}

void	initialize(t_p *p)
{
	int i;

	i = 0;
	p->a.start_t = actual_time();
	p->a.stop = 0;
	pthread_mutex_init(&p->a.write_mutex, NULL);
	while (i < p->a.total)
	{
		p->ph[i].id = i + 1;
		p->ph[i].ms_eat = 0;
		p->ph[i].nb_eat = 0;
		p->ph[i].r_f = (malloc(sizeof(pthread_mutex_t) * 1));
		pthread_mutex_init(&p->ph[i].l_f, NULL); // chaque philosopher detient sa propre fourchette a gauche
		if (i == p->a.total - 1)
			p->ph[i].r_f = &p->ph[0].l_f;
		else
			p->ph[i].r_f = &p->ph[i + 1].l_f; // et emprunte celle de son voisin de droite
		i++;
	}
}