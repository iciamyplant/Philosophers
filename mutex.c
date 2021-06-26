#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

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

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef	struct              s_p
{
    pthread_mutex_t         mutex;
    int                     i;
}                           t_p;

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

pthread_mutex_t         write_mutex = PTHREAD_MUTEX_INITIALIZER;

void    write_status(int start)
{
    long int now_sec;
    long int now_usec;
    long int time;
    struct timeval current_time;

    now_sec = 0;
    now_usec = 0;
    time = 0;
    pthread_mutex_lock(&write_mutex);
    gettimeofday(&current_time, NULL);
    now_sec = current_time.tv_usec;
    time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
    printf("now = %d\n", now_sec);
    //printf("start time = %d\n", ph->pa->ms);
    //ft_putnbr_fd(((now - start) / 1000), 1);
    //ft_putstr_fd(" Philo is blabla\n", 1);
    pthread_mutex_unlock(&write_mutex);
}

void    *go1(void *pp)
{
    struct timeval current_time;
    int start;
    int i = 0;

    t_p *ppp;

    ppp = (t_p *)pp;
    gettimeofday(&current_time, NULL);
    start = current_time.tv_usec;
    while (i < 30)
    {
        write_status(start);
        //sleep(1);
    }
    return (NULL);
}

int main()
{
    pthread_t               thread_id1;
    pthread_t               thread_id2;
    t_p                     p;
    t_p                     *pp;

    pp = (malloc(sizeof(t_p) * 1));
    pp = &p;
    p.i = 3;

    pthread_mutex_init(&p.mutex, NULL);
    pthread_create(&thread_id1, NULL, go1, (void *)pp);
    pthread_create(&thread_id2, NULL, go1, (void *)pp);
    sleep(1);
}