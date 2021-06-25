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

typedef	struct              s_arg //arguments of ./philo
{
	int                     total;
    int                     die;
    int                     eat;
    int                     sleep;
    int                     m_eat; //must eat m_eat times
    long int                s;  // start time in seconds
    int                     ms; // start time in microseconds
}                           t_arg;

typedef	struct              s_philo
{
	int                     id;
    pthread_t               thread_id;
    pthread_mutex_t         r_f;    // right fork
    pthread_mutex_t         l_f;    // left fork
    int                     r_fid;  // the id of the last philosopher who used this fork
    int                     l_fid;  // the id of the last philosopher who used this fork
    t_arg                   *pa;    // pointer to structure with all arguments
    int                     ms_eat; // time of eat, changing each time when philospher is eating
    int                     nb_eat; // each time the philosopher eats nb_eat++
}                           t_philo;

typedef	struct              s_p
{
    t_philo                 *ph;    // structure for each philosophe
    t_arg                   a;      //structure with arguments, same for all philosophers
}                           t_p;

/*
** functions
*/

int     parse_args(int argc, char **argv, t_p *p);
int     initialize(t_p *p);
void    *myThreadFun(void *data);
int     ft_exit(char *str);
void    status_eating();
void    status_fork();

#endif