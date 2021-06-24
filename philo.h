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

typedef	struct              s_arg
{
	int                     total;
    int                     die;
    int                     eat;
    int                     sleep;
    int                     m_eat;
    long int                s;  // start time in seconds
    int                     ms; // start time in microseconds
}                           t_arg;

typedef	struct              s_philo
{
	int                     id;
    pthread_t               thread_id;
    pthread_mutex_t         r_f; // right fork
    pthread_mutex_t         l_f; // left fork
    int                     r_fid; // the id of the last philosopher who used this fork
    int                     l_fid; // the id of the last philosopher who used this fork
    t_arg                   *pa;
}                           t_philo;

typedef	struct              s_p
{
    t_philo                 *ph; // structure for each philosophe
    t_arg                   a;   //structure with arguments, same for all philosophers
}                           t_p;

/*
** functions
*/

int     parse_args(int argc, char **argv, t_p *p);
void    eating(t_philo *ph);
int     initialize(t_p *p);
int     ft_exit(char *str);

#endif