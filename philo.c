//TODO TODAY BEFORE GOING TO BED :
	//THE MANDATORY IS READY TO PUSH ( )
		//CHECK WHERE I WAS AT YESTERDAY			(√)
		//CLEAN THE CODE IN 30MIN						( )
		//ADD THE FULL-MEALS OPTION					(√)
		//ADD THE MORE MUTEXE PROTECTION			(√)
		//PUSH THE MANDATORY AS READY				( )




#include "philo.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	i--;
	while (s && is_space(s[i]))
		i--;
	return (i);
}

long	ft_atoi(char *s)
{
	long	n;
	int		i;

	i = 0;
	n = 0;
	while (s && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
		i++;
	if(s && (s[i] == '-' || s[i] == '+'))
		if (s[i++] == '-')
			return (-1);
	while (s && s[i])
	{
		if (((s[i] > '9' || s[i] < '0') && !is_space(s[i])) \
		|| (is_space(s[i]) && i < ft_strlen(s)))
			return (-1);
		else if (s[i] <= '9' && s[i] >= '0')
			n = n * 10 + (s[i] - 48);
		i++;
	}
	return (n);
}

int	parsing(char **av, data_t *data)
{
	data->num_of_philos = ft_atoi(av[1]);
	if (data->num_of_philos <= 0)
		return (-1);
	data->time2die = ft_atoi(av[2]);
	if (data->time2die <= -1)
		return (-1);
	data->time2eat = ft_atoi(av[3]);
	if (data->time2eat <= -1)
		return (-1);
	data->time2sleep = ft_atoi(av[4]);
	if (data->time2sleep <= -1)
		return (-1);
	data->num_of_meals = ft_atoi(av[5]);
	if (data->num_of_meals <= -1)
		return (-1);
	if (!av[5])
		data->num_of_meals = -1;
	if (data->num_of_philos > 200 || data->num_of_philos <= 0)
		return (-1);
	return (1);
}
long	get_time()
{
	struct timeval	time;
	if (gettimeofday(&time, NULL) != 0)
	{
		perror("gettimeofday");
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
int init_philos(data_t *data, philo_t **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(philo_t) * data->num_of_philos);
	if (!*philo)
		return (-1);
	data->simu_done = 0;
	data->start_time = get_time();
	while (i < data->num_of_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].l_fork = i;
		if ((*philo)[i].id == data->num_of_philos)
			(*philo)[i].r_fork = 0;
		else
			(*philo)[i].r_fork = i + 1;
		(*philo)[i].data = data; //assigning the data struct to each philo
		(*philo)[i].last_meal = data->start_time;
		(*philo)[i].meal_count  = 0;
		i++;
	}
	return (1);
}

void 	seter(pthread_mutex_t *mutex, long *var, long value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}
long	geter(pthread_mutex_t *mutex, long *var)
{
	long	value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

int init_forks(data_t *data)
{
	int	i;
	
	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (-1);
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mtx, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->last_meal, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->simu_done_mtx, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->num_of_philos_mtx, NULL) != 0)//
		return (-1);
	if (pthread_mutex_init(&data->meal_cnt_mtx, NULL) != 0)
		return (-1);
	return (1);
}

void	print_fun(int flag, int id, data_t *data)
{
	long	timestamp;

	pthread_mutex_lock(&data->simu_done_mtx);
	if (!data->simu_done)
	{
		pthread_mutex_lock(&data->print_mtx);
		timestamp = get_time() - data->start_time;
		if (flag == FORK)
			printf("%ld %d has taken a fork\n", get_time() - data->start_time, id);
		else if (flag == EAT)
			printf("%ld %d is eating\n", get_time() - data->start_time, id);
		else if (flag == SLEEP)
			printf("%ld %d is sleeping\n", get_time() - data->start_time, id);
		else if (flag == THINK)
			printf("%ld %d is thinking\n", get_time() - data->start_time, id);
		pthread_mutex_unlock(&data->print_mtx);
	}
	pthread_mutex_unlock(&data->simu_done_mtx);
}

int	eating(philo_t *philo)
{
	data_t *data;
	long	start_action;
	long	meal_count;

	data = philo->data;
	meal_count = geter(&data->meal_cnt_mtx, &philo->meal_count);
		// pthread_mutex_lock(&data->print_mtx);
		// printf("mela_cout :%ld\n", geter(&data->meal_cnt_mtx, &philo->meal_count));
		// pthread_mutex_unlock(&data->print_mtx);
	
	// if (philo->meal_count == data->num_of_meals)
	// {
		// pthread_mutex_lock(&data->print_mtx);
		// printf("break in eat\n");
		// pthread_mutex_unlock(&data->print_mtx);
	// 	return (BREAK);
	// }

	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	print_fun(FORK, philo->id, philo->data);

	if (data->num_of_philos == 1)					// PROTECT THE CASE OF 1 PHILOSOPHER
		return (BREAK);

	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	print_fun(FORK, philo->id, philo->data);

	print_fun(EAT, philo->id, data);
	start_action = get_time();
	seter(&data->last_meal, &philo->last_meal, get_time());

	while (!geter(&data->simu_done_mtx, &data->simu_done) \
	&& (get_time() - start_action < data->time2eat))
		usleep(250);
	
	seter(&data->meal_cnt_mtx, &philo->meal_count, meal_count + 1);

	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	return (0);
}

void	sleeping(philo_t *philo)
{
	data_t	*data;
	long	start_action;

	data = philo->data;
	start_action = get_time();
	print_fun(SLEEP, philo->id, data);
	while (!geter(&data->simu_done_mtx, &data->simu_done) \
	&& (get_time() - start_action < data->time2sleep))
		usleep(250);
}

void	thinking(philo_t *philo)
{
	data_t	*data;

	data = philo->data;
	print_fun(THINK, philo->id, data);
}

void routine(void *arg)
{
	philo_t *philo = (philo_t *)arg;
	// data_t	*data = philo->data;

	if (philo->id % 2 == 0)
		sleeping(philo);

	while (1)
	{
		if (geter(&philo->data->simu_done_mtx, &philo->data->simu_done))
			break;
		thinking(philo);
		if (eating(philo) == BREAK)
			break;
		sleeping(philo);
	}
}
int	is_full(philo_t *philo)
{
	data_t	*data;
	int		is_full;
	int		i;

	i = 0;
	is_full = 0;
	data = philo[0].data;
	while (i < data->num_of_philos)
	{
		if (geter(&data->meal_cnt_mtx, &philo[i].meal_count) == data->num_of_meals)
			is_full++;
		i++;
	}
	if (is_full == data->num_of_philos)
		return (1);
	return (0);
}
void	monitor(void *arg)
{
	philo_t	*philo;
	data_t	*data;
	int		i;
	
	i = 0;
	philo = (philo_t *)arg;
	data = philo[0].data;
	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			// printf("time_from_last_meal :%ld\n", (get_time() - philo[i].last_meal));
			// printf("last_meal :%ld\n\n",  philo[i].last_meal);

			if ((geter(&data->last_meal, &philo[i].last_meal) && \
			(get_time() - geter(&data->last_meal, &philo[i].last_meal)) >= data->time2die))
			{
				// pthread_mutex_lock(&data->simu_done_mtx);
				// data->simu_done = 1;
				// pthread_mutex_unlock(&data->simu_done_mtx);
				seter(&data->simu_done_mtx, &data->simu_done, 1);
				pthread_mutex_lock(&data->print_mtx);
				printf("%ld %ld died\n", get_time() - data->start_time, philo[i].id);
				pthread_mutex_unlock(&data->print_mtx);
				// printf("BRUH STILL ALIVE\n");
				return ;
			}
			if (is_full(philo))
			{
				seter(&data->simu_done_mtx, &data->simu_done, 1);
				return ;
			}

			i++;
		}
		usleep(250);
	}
}

int init_threads(data_t *data, philo_t *philo)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc (sizeof(pthread_t) * (data->num_of_philos));
	while (i < data->num_of_philos)
	{
		if (pthread_create(&threads[i], NULL, (void *)routine, &philo[i]) != 0)
		{
			perror("pthread_create :");
			return (-1);
		}
		i++;
	}
	monitor(philo);
	i = 0;
	while (i < data->num_of_philos)
		pthread_join(threads[i++], NULL);
	
	free(threads);
	return (1);
}

int	main(int ac, char **av)
{
	
	data_t data;
	philo_t *philos;
	
	if (ac != 5 && ac != 6)
		return (printf("the program takes : nbr_of_philos, time2die, time2eat,"\
		" time2sleep, [nbr_times_each_philo_must_eat]"));
	if (parsing(av, &data) == -1)
	{
		printf("ERROR :INCORRECT VALUES\n");
		return (1);
	}
	if (init_philos(&data, &philos) < 0)
		return (1);
	init_forks(&data);

	init_threads(&data, philos);


	// for (int i = 0; i < ac ; i++)
	// {
	// 	printf("%d :%s\n", i, av[i]);
	// }
	// PRINTING DATA;
		// printf("data.num_of_philos :%ld\n", data.num_of_philos);
		// printf("data.time2die  	   :%ld\n", data.time2die);
		// printf("data.time2eat	   :%ld\n", data.time2eat);
		// printf("data.time2sleep	   :%ld\n", data.time2sleep);
		// printf("data.num_of_meals  ;%ld\n", data.num_of_meals);
}
