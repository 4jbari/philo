//TODO TODAY BEFORE GOING HOME:
	//*(1) MONITOR; ** 6:00 									()
	//*(2) FIX THE SPLITTING OF THE PHILOS ROUTINE ** 6:45		()
	//*(3) SET THE NEW TASKS **BEFORE ** 6						()



#include "philo.h"

long	ft_atoi(char *s)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (s && (s[i] == '-' || s[i] == '+'))
		if (s[i++] == '-')
		{
			printf("ERROR :NEGATIVE NUMBERS");
			return (-1);
		}
	while (s && *s)
	{
		if (*s > '9' || *s < '0')
		{
			printf("ERROR :INCORRECT VALUES");
			return (-1);
		}
		else
		{
			n = n * 10 + (*s - 48);
			s++;
		}
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
	// if (data->num_of_philos <= 0 || data->time2die <= 0 || data->time2eat <= 0
	// 	|| data->time2sleep <= 0 || data->num_of_meals < 0)
	// 	return (-1);
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
	while (i < data->num_of_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].l_fork = i;
		if ((*philo)[i].id == data->num_of_philos)
			(*philo)[i].r_fork = 0;
		else
			(*philo)[i].r_fork = i + 1;
		(*philo)[i].data = data; //assigning the data struct to each philo
		(*philo)[i].last_meal = 0;
		i++;
	}
	data->start_time = get_time();
	// printf("start_time :%ld", data->start_time);


	//remove below
	// i = 0;
	// while (i < data->num_of_philos)
	// {
	// 	printf("philo id = %d, left fork %d, right fork %d, time2die :%ld\n", (*philo)[i].id, (*philo)[i].l_fork, (*philo)[i].r_fork, (*philo)[i].data->time2die);
		
	// 	i++;
	// }
	return (1);
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
	return (1);
}

void	print_fun(int flag, int id, data_t *data)
{
	long	timestamp;

	pthread_mutex_lock(&data->print_mtx);
	timestamp = get_time() - data->start_time;
	if (flag == 0)
		printf("%ld %d has taken a fork\n", get_time() - data->start_time, id);
	else if (flag == 1)
		printf("%ld %d is eating\n", get_time() - data->start_time, id);
	else if (flag == 2)
		printf("%ld %d is sleeping\n", get_time() - data->start_time, id);
	else if (flag == 3)
		printf("%ld %d is thinking\n", get_time() - data->start_time, id);
	pthread_mutex_unlock(&data->print_mtx);
}

void	eating(philo_t *philo)
{
	data_t *data;

	data = philo->data;
	philo->last_meal = get_time();
	print_fun(1, philo->id, data);
	while (get_time() - data->start_time < data->time2eat)
		usleep(250);
}
void	sleeping(philo_t *philo)
{
	data_t	*data;

	data = philo->data;
	print_fun(2, philo->id, data);
	while (get_time() - data->start_time < data->time2sleep)
		usleep(250);
	
}
void	thinking(philo_t *philo)
{
	data_t	*data;

	data = philo->data;
	print_fun(3, philo->id, data);
}
void routine(void *arg)
{
	philo_t *philo = (philo_t *)arg;

//lock
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	//philo takes fork1 (printf p1 toke fork)
		print_fun(0, philo->id, philo->data);
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	//philo takes fork2 (printf p2 toke fork)
		print_fun(0, philo->id, philo->data);
	//eating()
		eating(philo);
//unlock
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);

	
//sleeping(); (printf 4 a time)
	sleeping(philo);
//thinking(); (printf 4 a time)
	thinking(philo);
}

void	monitor(void *arg)
{
	philo_t	*philo;
	data_t	data;
	int		i;
	
	i = 0;
	philo = (philo_t *)arg;
	data = data;
	while (1)
	{
		i = 0;
		while (i < data.num_of_philos)
		{
			if (get_time() - philo->last_meal > data.time2die)
			{
				data.simu_end = 1;
				return ;
			}
			i++;
		}
	}
}

int init_threads(data_t *data, philo_t *philo)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc (sizeof(pthread_t) * (data->num_of_philos + 1)); //+1 for the monitor's thread
	while (i < data->num_of_philos)
	{
		if (pthread_create(&threads[i], NULL, (void *)routine, &philo[i]) != 0)
		{
			perror("pthread_create :");
			return (-1);
		}
		i++;
	}

	if (pthread_create(&threads[i], NULL, (void *)monitor, philo))
		return (-1);
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
		return (-1);
	
	init_philos(&data, &philos);

	init_forks(&data);
	init_threads(&data, philos);



	// printf("%ld", sysconf(_SC_CLK_TCK));

	//PRINTING DATA;

	// printf("%ld\n", data.num_of_philos);
	// printf("%ld\n", data.time2die);
	// printf("%ld\n", data.time2eat);
	// printf("%ld\n", data.time2sleep);
	// printf("%ld\n", data.num_of_meals);
} 
