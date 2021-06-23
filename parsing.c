#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
    i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	return (sum);
}

int     numeric(char **argv)
{
    int j = 1;
    int i = 0;

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

int    parse_args(int argc, char **argv, t_p *p)
{
    if ((argc == 5 || argc == 6) && numeric(argv))
    {
        p->a.total = ft_atoi(argv[1]);
        p->a.die = ft_atoi(argv[2]);
        p->a.eat = ft_atoi(argv[3]);
        p->a.sleep = ft_atoi(argv[4]);
        if (argc == 6)
            p->a.m_eat = ft_atoi(argv[5]);
        return (1);
    }
    return (0);
}