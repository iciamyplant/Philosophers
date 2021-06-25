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

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;

	ln = (long)n;
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

pthread_mutex_t         write_mutex = PTHREAD_MUTEX_INITIALIZER;

void    write_status(char *str, t_philo *ph)
{
    int now;
    struct timeval current_time;

    now = 0;
    pthread_mutex_lock(&write_mutex);
    gettimeofday(&current_time, NULL);
    now = current_time.tv_usec;
    //printf("now = %d\n", now);
    //printf("start time = %d\n", ph->pa->ms);
    ft_putnbr_fd(((now - ph->pa->ms) / 1000), 1);
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
    struct timeval current_time;
    int i;

    i = 0;
    if (gettimeofday(&current_time, NULL) == -1)
        return (0);
    p->a.s = current_time.tv_sec;
    p->a.ms = current_time.tv_usec;
    while (i < p->a.total)
    {
        p->ph[i].id = i + 1;
        pthread_mutex_init(&p->ph[i].r_f, NULL);
        if (i == p->a.total - 1)
            p->ph[i].r_f = p->ph[0].l_f;
        else
            p->ph[i].r_f = p->ph[i + 1].l_f; // chaque philosopher detient sa fourchette a gauche et emprunte celle de son voisin de droite
        //pthread_mutex_init(p->ph[i].l_f, NULL);
        i++;
    }
    return (1);
}