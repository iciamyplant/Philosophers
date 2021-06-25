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
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}

pthread_mutex_t         write_status = PTHREAD_MUTEX_INITIALIZER;

void    status_fork()
{
    char *str;

    str = "take forks \n";
    pthread_mutex_lock(&write_status);
    ft_putstr_fd("Philo ", 1);
    ft_putstr_fd(str, 1);
    pthread_mutex_unlock(&write_status);
}

void    status_eating()
{
    char *str;

    str = "is eating \n";
    pthread_mutex_lock(&write_status);
    ft_putstr_fd("Philo ", 1);
    ft_putstr_fd(str, 1);
    pthread_mutex_unlock(&write_status);
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
        if (i == p->a.total - 1)
            p->ph[i].r_f = p->ph[0].l_f;
        else
            p->ph[i].r_f = p->ph[i + 1].l_f; // chaque philosopher detient sa fourchette a gauche et emprunte celle de son voisin de droite
        //pthread_mutex_init(p->ph[i].l_f, NULL);
        i++;
    }
    return (1);
}