// TODAY NOT GOING HOME UNTIL:
// (1) starting the simulation with routine () 

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
		i++;
	}
	data->start_time = get_time();
	printf("start_time :%ld\n", data->start_time);


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
	pthread_mutex_lock(&data->print_mtx);

	//print the log

	pthread_mutex_unlock(&data->print_mtx);





}

void	eating(data_t *data)
{
	print_fun();
	while (get_time() - data->start_time < data->time2eat)
		usleep(250);
}
void	sleeping(data_t *data)
{



}

void routine(void *arg)
{
	philo_t *philo = (philo_t *)arg;

	pthread_mutex_lock(&philo->data->print_mtx);
	printf("TEST%d\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mtx);
//lock
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	pthread_mutex_lock(&philo->data->print_mtx);
	//philo takes fork1 && fork2 (printf p1 toke fork)
		printf("%ld philo :%d  has taken a fork\n", (get_time() - philo->data->start_time),  philo->id);
		printf("%ld philo :%d  has taken a fork\n", (get_time() - philo->data->start_time), philo->id);
	//eating()
		eating(philo->data);
//unlock
	pthread_mutex_unlock(&philo->data->print_mtx);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);

	
//sleeping(); (printf 4 a time)
	sleeping(philo->data);
	//thinking(); (printf 4 a time)
	thinking(philo->data);
}
int init_threads(data_t *data, philo_t *philo)
{
	int	i;
	pthread_t *threads;


	i = 0;
	threads = malloc (sizeof(pthread_t) * data->num_of_philos);
	while (i < data->num_of_philos)
	{
		if (1)
		{
			if (i % 2 == 0 && pthread_create(&threads[i], NULL, (void *)routine, &philo[i]) != 0)
			{
				perror("pthread_create :")	;
				return (-1);
			}
		}
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (1);

}

int	main(int ac, char **av)
{
	printf("ac:%d\n", ac);
	
	data_t data;
	philo_t *philos;
	
	
	if (ac != 5 && ac != 6)
		return (printf("the program takes : nbr_of_philos, time2die, time2eat,"\
		 " time2sleep, [nbr_times_each_philo_must_eat]"));
	if (parsing(av, &data) == -1)
		return (-1);
	
	init_philos(&data, &philos);
	
	
	init_forks(&data);

	printf("return of init_threads :%d\n", 	init_threads(&data, philos));



	// printf("%ld", sysconf(_SC_CLK_TCK));

	//PRINTING DATA;

	// printf("%ld\n", data.num_of_philos);
	// printf("%ld\n", data.time2die);
	// printf("%ld\n", data.time2eat);
	// printf("%ld\n", data.time2sleep);
	// printf("%ld\n", data.num_of_meals);
} 
