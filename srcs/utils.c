#include "../include/philo.h"

void			ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void			ft_putstr_fd(char *s, int fd)
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

void			ft_putnbr_fd(long int ln, int fd)
{
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

long int		actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
}

void			write_status(char *str, t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->write_mutex);
	ft_putnbr_fd(actual_time() - ph->pa->start_t, 1);
	ft_putstr_fd(" Philo ", 1);
	ft_putnbr_fd(ph->id, 1);
	ft_putstr_fd(str, 1);
	pthread_mutex_unlock(&ph->pa->write_mutex);
}