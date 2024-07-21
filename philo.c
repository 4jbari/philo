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
			printf("NEGATIVE NUMBERS");
			return (-1);
		}
	while (s && *s)
	{
		if (*s > '9' || *s < '0')
		{
			printf("INCORRECT VALUES");
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
	data->time2die = ft_atoi(av[2]);
	data->time2eat = ft_atoi(av[3]);
	data->time2sleep = ft_atoi(av[4]);
	data->num_of_meals = ft_atoi(av[5]);
	if (data->num_of_philos <= 0 || data->time2die <= 0 || data->time2eat <= 0
		|| data->time2sleep <= 0 || data->num_of_meals < 0)
		return (-1);
	return (1);
}


// sleeo 

// eat()
// {
// 	pthread_mutex_lock();
	
// 	pthread_mutex_lock()
// 	sleep(4)
	
// 	unlock
// }

// routine {

// 	while (1)
// 	{
// 		lock(mutex1);
// 		eat()
// 		sleep()
// 		think()
// 		unlock(mutex1);
// 	}

// }

// void init_threads(data_t data)
// {

// } 

int init_philos(data_t data, philo_t **philo)
{
	int	i;

	i = 0;
	printf("boom\n");
	*philo = malloc(sizeof(philo_t) * data.num_of_philos);
	if (!*philo)
		return (-1);
	while (i < data.num_of_philos)
	{
		(*philo)[i].id = i + 1;
		if ((*philo)[i].id == data.num_of_philos)
			(*philo)[i].L_fork = 0;
		else
			(*philo)[i].L_fork = i + 1;
		(*philo)[i].R_fork = i;
		(*philo)[i].data = data; //assigning the data struct to each philo
		i++;
	}
	//remove below
	i = 0;
	while (i < data.num_of_philos)
	{
		printf("i:%d | id:%d\n", i, philo[i]->id);
		printf("L:%d\n", philo[i]->L_fork);
		printf("R:%d\n", philo[i]->R_fork);
		i++;
	}
	return (1);
}
int init_forks(data_t data)
{
	int	i;
	
	i = 0;
	data.forks = malloc(sizeof(pthread_mutex_t) * data.num_of_philos);
	if (!data.forks)
		return (-1);
	while (i < data.num_of_philos)
	{
		if (pthread_mutex_init(&data.forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (1);

}
void routine(data_t data, philo_t philo)
{
	pthread_mutex_lock(&data.forks[philo.L_fork]);
	pthread_mutex_lock(&data.forks[philo.L_fork]);
	int i = 0;

	printf("routine:%d\n", i++);

	pthread_mutex_lock(&data.forks[philo.L_fork]);
	pthread_mutex_lock(&data.forks[philo.L_fork]);



}
int init_threads(data_t data, philo_t *philo)
{
	int	i;
	pthread_t *threads;


	i = 0;
	threads = malloc (sizeof(pthread_t) * data.num_of_philos);
	while (i < data.num_of_philos)
	{
		if (pthread_create(&threads[i], NULL, (void *)routine, &philo[i]) != 0)
			return (-1);
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
		return (printf("WRONG ARGUMENTS"));
	if (parsing(av, &data) == -1)
    {
        printf("WRONG ARGUMENT: should be bigger than 0\n");
		return (-1);
    }
	
	printf("tesst\n");
	init_philos(data, &philos);
	init_forks(data);
	init_threads(data, philos);

	int i = 0;
	// while (i < data.num_of_philos)
	// {
	// 	printf("L:%d\n", data.philo->L_fork);
	// 	printf("R:%d\n", data.philo->R_fork);
	// 	i++;
	// }
	// init_forks()

	// init_threads(data);









	// printf("%ld\n", data.num_of_philos);
	// printf("%ld\n", data.time2die);
	// printf("%ld\n", data.time2eat);
	// printf("%ld\n", data.time2sleep);
	// printf("%ld\n", data.num_of_meals);
}