# Philosophers


  ```
 typedef	struct        s_arg             //arguments after ./philo
{
	int                   total;            // number of philosophers
	int                   die;              // time to die in milliseconds
	int                   eat;              // time to eat in milliseconds
	int                   sleep;            // time to sleep in milliseconds
	int                   m_eat;            // must eat m_eat times
	long int              start_t;          // start time in milliseconds
	pthread_mutex_t       write_mutex;      // write mutex
	pthread_mutex_t       count;
	pthread_mutex_t       test;
	int                   nb_p_finish;      // when a philosopher ate m_eat times : nb_p_finish++
	int                   stop;             // 0 if none philosopher is dead, 1 if a philosopher is dead, 2 if all philosophers ate m_eat times
}                       t_arg;

typedef	struct          s_philo
{
	int                   id;               // id of the philosopher
	pthread_t             thread_id;        // thread id
	pthread_t             thread_death_id;  // id of the thread monitoring death
	pthread_mutex_t       *r_f;             // right fork mutex
	pthread_mutex_t       l_f;              // left fork mutex
	t_arg                 *pa;              // pointer to structure with all arguments (pointer on a)
	long int              ms_eat;           // time of the last dinner in milliseconds
	unsigned int          nb_eat;           // number of dinners (each time the philosopher eats nb_eat++)
	int                   finish;           // 1 when a philosopher ate m_eat times, if not, 0
}                       t_philo;

typedef	struct          s_p
{
	t_philo               *ph;              // structure for each philosopher
	t_arg                 a;                // structure with arguments, same for all philosophers
}
  ```
  
  
  ```
while (i < p->a.total)
{
		p->ph[i].id = i + 1;
		pthread_mutex_init(&p->ph[i].l_f, NULL);  // chaque philosopher detient sa propre fourchette a gauche
		if (i == p->a.total - 1)
			p->ph[i].r_f = &p->ph[0].l_f;           // et emprunte celle de son voisin de droite
		else
			p->ph[i].r_f = &p->ph[i + 1].l_f;       // et emprunte celle de son voisin de droite
		i++;
}
```

```
long int		actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
}
```
