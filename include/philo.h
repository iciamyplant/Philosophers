#ifndef PHILO_H
# define PHILO_H

/*
** libraries
*/

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

/*
** structures
*/

typedef	struct				s_arg		//arguments after ./philo
{
	int						total;		// number of philosophers
	int						die;		// time to die in milliseconds
	int						eat;		// time to eat in milliseconds
	int						sleep;		// time to sleep in milliseconds
	int						m_eat;		// must eat m_eat times
	long int				start_t;	// start time in milliseconds
	pthread_mutex_t			write_mutex;// write mutex
	//pthread_mutex_t			death;
	int						nb_p_finish;// when a philosopher ate m_eat times : nb_p_finish++
	int						stop;		// 0 if none philosopher is dead, 1 if a philosopher is dead, 2 if all philosophers ate m_eat times
}							t_arg;

typedef	struct				s_philo
{
	int						id;			// id of the philosopher
	pthread_t				thread_id;	// thread id
	pthread_t				thread_death_id; // id of the thread monitoring death
	pthread_mutex_t			*r_f;		// right fork mutex
	pthread_mutex_t			l_f;		// left fork mutex
	t_arg					*pa;		// pointer to structure with all arguments (pointer on a)
	long int				ms_eat;		// time of the last dinner in milliseconds
	int						nb_eat;		// number of dinners (each time the philosopher eats nb_eat++)
} 							t_philo;

typedef	struct				s_p
{
	t_philo					*ph;		// structure for each philosopher
	t_arg					a;			// structure with arguments, same for all philosophers
}							t_p;

/*
** functions
*/

int				parse_args(int argc, char **argv, t_p *p);
int				initialize(t_p *p);
void			*thread(void *data);
int				ft_exit(char *str);
void			write_status(char *str, t_philo *ph);
long int		actual_time(void);
void			ft_putstr_fd(char *s, int fd);
void			ft_usleep(long int time_in_ms);
int				threading(t_p *p);
void			activity(t_philo *ph);

void			ft_putnbr_fd(long int ln, int fd);

#endif