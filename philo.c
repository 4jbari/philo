//TODO TODAY BEFORE GOING TO BED :
	//THE MANDATORY IS READY TO PUSH ( )
		//CHECK WHERE I WAS AT YESTERDAY			(√)
		//CLEAN THE CODE IN 30MIN						( )
		//ADD THE FULL-MEALS OPTION					(√)
		//ADD THE MORE MUTEXE PROTECTION			(√)
		//PUSH THE MANDATORY AS READY				( )

#include "philo.h"

void	print_fun(int flag, int id, t_data *data)
{
	long	timestamp;

	pthread_mutex_lock(&data->simu_done_mtx);
	if (!data->simu_done)
	{
		pthread_mutex_lock(&data->print_mtx);
		timestamp = get_time() - data->start_time;
		if (flag == FORK)
			printf("%ld %d has taken a fork\n", \
			get_time() - data->start_time, id);
		else if (flag == EAT)
			printf("%ld %d is eating\n", \
			get_time() - data->start_time, id);
		else if (flag == SLEEP)
			printf("%ld %d is sleeping\n", \
			get_time() - data->start_time, id);
		else if (flag == THINK)
			printf("%ld %d is thinking\n", \
			get_time() - data->start_time, id);
		pthread_mutex_unlock(&data->print_mtx);
	}
    else if (flag == DEAD)
        printf("%ld %d died\n", \
		get_time() - data->start_time, id);
	pthread_mutex_unlock(&data->simu_done_mtx);
}

int	is_full(t_philo *philo)
{
	t_data	*data;
	int		is_full;
	int		i;

	i = 0;
	is_full = 0;
	data = philo[0].data;
	while (i < data->num_of_philos)
	{
		if (geter(&data->meal_cnt_mtx, \
		&philo[i].meal_count) == data->num_of_meals)
			is_full++;
		i++;
	}
	if (is_full == data->num_of_philos)
		return (1);
	return (0);
}

void	monitor(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (geter(&data->last_meal, &philo[i].last_meal) && \
			(get_time() - geter(&data->last_meal, &philo[i].last_meal)) \
			>= data->time2die)
			{
				seter(&data->simu_done_mtx, &data->simu_done, 1);
                print_fun(DEAD, philo[i].id, data);
				return ;
			}
			if (is_full(philo))
				return (seter(&data->simu_done_mtx, &data->simu_done, 1));
			i++;
		}
		usleep(250);
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (printf("the program takes : nbr_of_philos, time2die, "\
		"time2eat, time2sleep, [nbr_times_each_philo_must_eat]"));
	if (parsing(av, &data) == -1)
	{
		printf("ERROR :INCORRECT VALUES\n");
		return (1);
	}
	if (init_philos(&data, &philos) < 0)
		return (1);
	init_forks(&data);
	init_threads(&data, philos);
}
