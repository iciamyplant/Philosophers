#include "../include/philo.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd >= 0)
	{
		while (s && *s)
		{
            write(fd, &*s, 1);
			s++;
		}
	}
}

void	ft_putnbr_fd(long int ln, int fd)
{
	//long	ln;

	//ln = (long)n;
	if (ln < 0)
	{
		ln *= -1;
		ft_putchar_fd('-', fd);
	}
	if (ln >= 10)
	{
		ft_putnbr_fd(ln / 10, fd);
		ft_putnbr_fd(ln % 10, fd);
	}
	else
	{
		if (fd >= 0)
			ft_putchar_fd(ln + 48, fd);
	}
}

long int       actual_time(void)
{
    long int    time;
    struct      timeval current_time;
    time = 0;

    gettimeofday(&current_time, NULL);   
    time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
    return (time);
}

pthread_mutex_t         write_mutex = PTHREAD_MUTEX_INITIALIZER;

void    write_status(char *str, t_philo *ph)
{
    pthread_mutex_lock(&write_mutex);
    ft_putnbr_fd(actual_time() - ph->pa->start_t, 1);
    ft_putstr_fd(" Philo ", 1);
    ft_putnbr_fd(ph->id, 1);
    ft_putstr_fd(str, 1);
    pthread_mutex_unlock(&write_mutex);
}

int     ft_exit(char *str)
{
    printf("%s\n", str);
    return (-1);
}

int    initialize(t_p *p)
{
    int i;

    i = 0;
    p->a.start_t = actual_time();
    while (i < p->a.total)
    {
        p->ph[i].id = i + 1;
        pthread_mutex_init(&p->ph[i].r_f, NULL);
        if (i == p->a.total - 1)
            p->ph[i].r_f = p->ph[0].l_f;
        else
            p->ph[i].r_f = p->ph[i + 1].l_f; // chaque philosopher detient sa fourchette a gauche et emprunte celle de son voisin de droite
        i++;
    }
    return (1);
}