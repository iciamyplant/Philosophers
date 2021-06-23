#ifndef PHILO_H
# define PHILO_H

/*
** libraries
*/

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

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

typedef	struct			s_p
{
	t_arg              a; // arguments
}	                        t_p;




int    parse_args(int argc, char **argv, t_p *p);

#endif