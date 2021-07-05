# Philosophers

### Plan :
- Etape 1 - Bien comprendre le sujet
- Etape 2 - Se familiariser avec les threads et les mutex
- Etape 3 - Stratégie
- Etape 4 - Gestion du temps
- Etape 5 - Leaks, segfaults et data races
- Etape 6 - Tests

# Etape 1: Bien comprendre le sujet
Objectif : ne pas faire mourir les philosophes

- chaque philosophe est un **thread**, et chaque fourchette est un **mutex**
- ils font dans l'ordre : manger - dormir - penser (ils pensent pas vraiment, ils attendent d'avoir leurs fourchettes pour manger)
- pour manger ils doivent avoir deux fourchettes, sachant que y a que une fourchette par philosophe
- si y en a un qui meurt la simulation s'arrête et on doit afficher la mort dans maximum 10 ms
- ecrire chaque changement de statut de philosophe

./philo arg1 arg2 arg3 arg4 arg5

- arg1 = number_of_philosophers (nombre de philosophes et nombre de fourchettes)
- arg2 = time_to_die (s’il a pas mangé depuis time_to_die millisecondes il meurt)
- arg3 = time_to_eat (temps pour manger avec deux fourchettes en millisecondes)
- arg4 = time_to_sleep (temps pour dormir en milliseconde)
- arg5 = number_of_times_each_philosopher_must_eat (nombre de fois que chaque philosophe doit manger, arg optionnel)


Philo (=philo_one) : threads et mutexs.

Philo_bonus (=philo_three) : processus et semaphores.


# Etape 2: Se familiariser avec les threads et les mutex

Thread : chaque thread comprend ces éléments uniques. Et partage avec tous les autres threads du même processus : code section, data section, operating-system ressources comme les open files et les signals. Les processus contiennent toujours au moins un thread.

Faire le truc des printfs qui s'entre-melent pas


# Etape 3: Stratégie

- faire partir les nombres pairs avec du retard. Car si tous les philosophes commencent en meme temps et prennent leur fourchette droite personne ne pourra manger.
```
	if (ph->id % 2 == 0)
		ft_usleep(ph->pa->eat / 10);
```

- chaque philosophe a sa propre fourchette à gauche (l_f) et emprunte celle de son voisin a droite grache au pointeur (\*r_f) qui pointe sur la l_f du voisin de droite :

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

- expliquer comment check la mort

# Etape 4: Gestion du temps

- Pour connaitre le temps actuel en millisecondes avec gettimeofday :
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

- creer sa propre fonction ft_usleep car la vraie fonction attend au minimum le temps qu'on lui indique, donc pas precis
```
void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
````

# Etape 5: Leaks, segfaults et data races

**Data race** :
two or more threads in a single process access the same memory location concurrently, and at least one of the accesses is for writing, and the threads are not using any exclusive locks to control their accesses to that memory.
When these three conditions hold, the order of accesses is non-deterministic, and the computation may give different results from run to run depending on that order. Some data-races may be benign (for example, when the memory access is used for a busy-wait), but many data-races are bugs in the program.

Pour corriger les data races : **-g fsanitize=thread**

Message dans le discord : **valgrind --tool=helgrind** ou **valgrind --tool=drd** : si ceux-là renvoient des warnings ou des erreurs, c'est qu'il manque un mutex, ou qu'il est mal utilisé. Il faut vérifier manuellement, mais souvent, c'est signe que le projet n'est pas bon, même s'il semble marcher. 

# Etape 6: Tests

Forcement si on make avec fsanitize ou valgrind ca fonctionne moins bien

./philo 1 200 200 200





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
