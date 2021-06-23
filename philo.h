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
typedef	struct			s_arg
{
	int                 total;
    int                 die;
    int                 eat;
    int                 sleep;
    int                 m_eat;
}	                        t_arg;

typedef	struct			s_philo
{
	int                 id;
    pthread_t           thread_id;
}	                        t_philo;

typedef	struct			s_p
{
	t_arg              a; // arguments
    long int           s; // start time in seconds
    int                ms; // start time in microseconds
    t_philo            *ph; // structure for each philosophe
}	                        t_p;

/*
** functions
*/

int    parse_args(int argc, char **argv, t_p *p);

#endif