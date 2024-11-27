/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:46:52 by ajbari            #+#    #+#             */
/*   Updated: 2024/11/27 04:46:52 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	t_data	*data;
	long	start_action;
	long	meal_count;

	data = philo->data;
	meal_count = geter(&data->meal_cnt_mtx, &philo->meal_count);
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	print_fun(FORK, philo->id, philo->data);
	if (data->num_of_philos == 1)
		return (BREAK);
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	print_fun(FORK, philo->id, philo->data);
	print_fun(EAT, philo->id, data);
	start_action = get_time();
	seter(&data->last_meal, &philo->last_meal, get_time());
	while (!geter(&data->simu_done_mtx, &data->simu_done) \
	&& (get_time() - start_action < data->time2eat))
		usleep(500);
	seter(&data->meal_cnt_mtx, &philo->meal_count, meal_count + 1);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	return (0);
}

void	sleeping(t_philo *philo)
{
	t_data	*data;
	long	start_action;

	data = philo->data;
	start_action = get_time();
	print_fun(SLEEP, philo->id, data);
	while (!geter(&data->simu_done_mtx, &data->simu_done) \
	&& (get_time() - start_action < data->time2sleep))
		usleep(500);
}

void	thinking(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_fun(THINK, philo->id, data);
}

void	routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		sleeping(philo);
	while (1)
	{
		if (geter(&philo->data->simu_done_mtx, &philo->data->simu_done))
			break ;
		thinking(philo);
		if (eating(philo) == BREAK)
			break ;
		sleeping(philo);
	}
}
