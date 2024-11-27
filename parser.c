/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:43:49 by ajbari            #+#    #+#             */
/*   Updated: 2024/11/27 06:08:48 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (s && !*s)
		return (-1);
	while (s && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
		i++;
	if (s && (s[i] == '-' || s[i] == '+'))
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

int	parsing(char **av, t_data *data)
{
	data->num_of_philos = ft_atoi(av[1]);
	if (data->num_of_philos <= 0)
		return (-1);
	data->time2die = ft_atoi(av[2]);
	if (data->time2die <= 0)
		return (-1);
	data->time2eat = ft_atoi(av[3]);
	if (data->time2eat <= 0)
		return (-1);
	data->time2sleep = ft_atoi(av[4]);
	if (data->time2sleep <= 0)
		return (-1);
	data->num_of_meals = ft_atoi(av[5]);
	if (data->num_of_meals <= 0 && av[5])
		return (-1);
	if (!av[5])
		data->num_of_meals = -1;
	if (data->num_of_philos > 200)
		return (-1);
	return (1);
}
