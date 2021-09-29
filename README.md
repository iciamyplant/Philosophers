### Lancement :
  ```
make && ./philo arg1 arg2 arg3 arg4 arg5
  ```

### Plan :
- Etape 1 - Bien comprendre le sujet
- Etape 2 - Se familiariser avec les threads et les mutex
- Etape 3 - Stratégie
- Etape 4 - Gestion du temps
- Etape 5 - Leaks, segfaults et data races
- Etape 6 - Tests
- Utilites des variables dans ma structure et culture g prog parallèle

# Etape 1: Bien comprendre le sujet
Objectif : ne pas faire mourir les philosophes

- chaque philosophe est un **thread**, et chaque fourchette est un **mutex**
- ils font dans l'ordre : manger - dormir - penser (ils pensent pas vraiment, ils attendent d'avoir leurs fourchettes pour manger)
- pour manger ils doivent avoir deux fourchettes, sachant que y a que une fourchette par philosophe
- si y en a un qui meurt la simulation s'arrête et on doit afficher la mort dans maximum 10 millisecondes
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

Thread : Y a toujours au minimum un thread par processus. Mais on peut en creer plus, et chaque thread comprend ces éléments uniques et ses elements partages avec tous les autres threads du meme processus (code section, data section, operating-system ressources comme les open files et les signals)... 

La librairies qui permettent de gerer les threads : pthread et openmp

```
pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]); //pour creer un thread avec pthread
```

Mais si deux threads d'un meme processus veulent acceder a la meme variable de la memoire partagee au meme moment ca cree des comportements indefinis (voir data races en dessous). D'ou l'utilisation de mutexs. Les mutexs bloquent un bout de code, et les autres threads doivent attendre pour executer ce bout de code. Comme une clé des toillettes, chacun son tour.

Exemple ici si on enleve les mutex str imprimee par thread 1 est chevauchee par str imprimee par le thread 2 et ca fera "treatdr e1a d:  1c o:u ccoouu ccoau  cvaa  v?a" :

```
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

void    *go1(void *pp)
{
    char *str;
    int i = 0;
    t_p *ppp;

    ppp = (t_p *)pp;
    str = "tread 1 : coucou ca va ? \n";
    pthread_mutex_lock(&ppp->mutex); // si on enleve ici
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    pthread_mutex_unlock(&ppp->mutex); // si on enleve ici
    return (NULL);
}

int main()
{
    pthread_t               thread_id1;
    pthread_t               thread_id2;
    t_p                     p;

    p.i = 3;

    pthread_mutex_init(&p.mutex, NULL);			// obligatoire de init le mutex
    pthread_create(&thread_id1, NULL, go1, (void *)&p);
    pthread_create(&thread_id2, NULL, go1, (void *)&p);
    sleep(1);
}
```

Donc : 
- Chaque fourchette a son propre mutex qui permet de la verrouiller lorsqu'un philosophe la prend.
- On utilise aussi un mutex partagé par tous les philosophes qui permet de print du texte sans mélange comme dans l'exemple au dessus.


[Tuto video que j'ai utilise pour commencer](https://www.youtube.com/watch?v=o_GbRujGCnM&t=377s)


# Etape 3: Stratégie

- Faire partir les philos pairs ou impairs avec du retard. Car si tous les philosophes commencent en meme temps et prennent leur fourchette droite personne ne pourra manger.
```
	if (ph->id % 2 == 0)
		ft_usleep(ph->pa->eat / 10);
```

- Chaque philosophe a sa propre fourchette à gauche (l_f) et emprunte celle de son voisin a droite grace au pointeur (\*r_f) qui pointe sur la l_f du voisin de droite :

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

- Obligee de checker la mort dans un thread a cote sinon ne se rend pas compte a temps si y en a un qui meurt. Mais par contre si le thread check en continue la si le philo est mort ca baisse trop les perfs. Donc a chaque fois qu'un philo va faire ses activites un thread qui check la mort se lance. Et ce thread va usleep(time_to_die) et ensuite checker si le philo est mort. 

```
pthread_create(&ph->thread_death_id, NULL, is_dead, data);

void	*is_dead(void	*data)
{
	ft_usleep(ph->pa->die + 1);
	if (!check_death(ph, 0) && !ph->finish && ((actual_time() - ph->ms_eat) \
		>= (long)(ph->pa->die)))
		le philo est mort
```


# Etape 4: Gestion du temps

| seconde | milliseconde | microseconde |
|----------|-------|-------|
| 1 | 1000 | 1e+6 |
| 0,001 | 1 | 1000 |

- Fonctionnement de gettimeofday :
```
   struct timeval current_time;
   gettimeofday(&current_time, NULL);
   printf("seconds : %ld\nmicro seconds : %d", current_time.tv_sec, current_time.tv_usec);
```

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

Message dans le discord : "**valgrind --tool=helgrind** ou **valgrind --tool=drd** : si ceux-là renvoient des warnings ou des erreurs, c'est qu'il manque un mutex, ou qu'il est mal utilisé. Il faut vérifier manuellement, mais souvent, c'est signe que le projet n'est pas bon, même s'il semble marcher."

- detache : des que le thread se finis sa memoire est clean. Attention a ce que le main ne se finisse pas avant qu'on est finis le thread
- joignable : ne detruit pas sa memoire quand il a finit. pthread_join bloque jusqu'a ce que le thread soit finis



# Etape 6: Tests

Avec fsanitize ou valgrind y a des moins bonnes perf bien sur

| test | resultat attendu |
|----------|-------|
| ./philo 1 200 200 200 | philo 1 ne prend qu'une fourchette et meurt au bout de 200 ms |
| ./philo 2 800 200 200 | personne ne meurt |
| ./philo 5 800 200 200 | personne ne meurt |
| ./philo 5 800 200 200 7 | la simulation s'arrete quand chaque philo a mange 7 fois|
| ./philo 4 410 200 200 | personne ne meurt |
| ./philo 4 310 200 200 | un philo meurt |
| ./philo 4 500 200 1.2 | argument invalide |
| ./philo 4 0 200 200 | argument invalide|
| ./philo 4 -500 200 200 | argument invalide |
| ./philo 4 500 200 2147483647 | un philo meurt au bout de 500 ms |
| ./philo 4 2147483647 200 200 | personne ne meurt |
| ./philo 4 214748364732 200 200 | argument invalide|
| ./philo 4 200 210 200 | un philo meurt, il faut afficher la mort avant 210 ms |



# Utilites des variables dans ma structure et culture g prog parallèle


**Programmation séquentielle** (ou linéaire) vs **programmation parallèle** :
Lorsque vous programmez vous faites de la programmation dite linéaire. Cette technique consiste à exécuter les instructions les unes après les autres afin d'obtenir le résultat souhaité. Lorsque au moins deux actions se déroulent en parallèle on parlera d’algorithme parallèle.

**Les architectures :**
- Les clusters de calcul (OCCIGEN (calculateur développé par atos), Turing (raspberry pi clusters), Muse) : (=grappe de serveurs, cluster, ferme de calcul, computer cluster) pour désigner des techniques consistant à regrouper plusieurs ordinateurs indépendants appelés nœuds, afin de permettre une gestion globale et de dépasser les limitations d'un ordinateur. Un groupe de serveurs mais vu de l'extérieur comme un seul serveur. Le cluster répond au besoin des demandes de traitement des applications en hausse, une demande forte de haute disponibilité des applications. Ex : le cluster actif/passif permet de doubler un serveur avec un deuxième serveur similaire en cas de panne. Permet de repartir la charge entre les serveurs.
- Les grilles informatique (France Grille) : réseau de ressources informatiques qui se transmettent des données.
- Les accélérateurs matériels (XeonPhi, GPU) : L'accélération matérielle consiste à confier une fonction spécifique effectuée par le processeur à un circuit intégré (= une puce electronique) dédié qui effectuera cette fonction de façon plus efficace. Pendant longtemps, les calculs effectués par les ordinateurs grand public étaient entièrement pris en charge par le processeur central (CPU). Or, ce processeur s'avérait insuffisant dans un certain nombre de domaines. On eut l'idée de créer des circuits plus efficaces que le processeur pour ces tâches afin de le décharger.
- machines vectorielles : Un processeur vectoriel est un processeur possédant diverses fonctionnalités architecturales lui permettant d'améliorer l’exécution de programmes utilisant massivement des tableaux, des matrices, et qui permet de profiter du parallélisme inhérent à l'usage de ces derniers.
- Les multi-coeurs

**Les méthodes de parallélisation :**
- Le calcul réparti
- Le calcul en mémoire partagée (Multithread) : a pour but d'augmenter l'utilisation d'un seul cœur en tirant profit des propriétés des threads et du parallélisme au niveau des instructions. Contrairement aux processus, les threads partagent la mémoire du processus qui les contient, ce qui rend les changements de contexte peu coûteux en temps. Un thread est donc un fil d'exécution, une tâche que doit exécuter le processeur. Un cœur ne peut exécuter qu'un seul thread à la fois. Donc, si un processeur a deux cœurs, deux threads (deux tâches) peuvent être exécutées simultanément et ainsi de suite.
- Le calcul en mémoire distribuée (MPI = Multiprocessing)

**Les erreurs classiques de la programmation parallèle**
- data race
- défaut de synchronisation
- incohérence des données


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
