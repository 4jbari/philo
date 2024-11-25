#include "philo.h"

int	init_threads(t_data *data, t_philo *philo)
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
	monitor(philo, data);
	i = 0;
	while (i < data->num_of_philos)
		pthread_join(threads[i++], NULL);
	// free(threads);
	return (1);
}

int	init_forks(t_data *data)
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
	if (pthread_mutex_init(&data->num_of_philos_mtx, NULL) != 0) //
		return (-1);
	if (pthread_mutex_init(&data->meal_cnt_mtx, NULL) != 0)
		return (-1);
	return (1);
}

int	init_philos(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * data->num_of_philos);
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
		(*philo)[i].data = data;
		(*philo)[i].last_meal = data->start_time;
		(*philo)[i].meal_count = 0;
		i++;
	}
	return (1);
}
