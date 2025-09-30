/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:40:49 by sungor            #+#    #+#             */
/*   Updated: 2025/07/28 23:40:50 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	init_mutexes(t_data *data)
{
	int	i;

	if (safe_mutex_init(&data->print_mutex) != 0)
		return (1);
	if (safe_mutex_init(&data->death_mutex) != 0)
	{
		safe_mutex_destroy(&data->print_mutex);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (safe_mutex_init(&data->forks[i]) != 0)
		{
			while (--i >= 0)
				safe_mutex_destroy(&data->forks[i]);
			safe_mutex_destroy(&data->death_mutex);
			safe_mutex_destroy(&data->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	assign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].forks_taken = 0;
		data->philos[i].full_reported = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		i++;
	}
	assign_forks(data);
	return (0);
}

int	init_all(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		free(data->philos);
		data->philos = NULL;
		return (1);
	}
	if (init_mutexes(data))
	{
		free(data->philos);
		free(data->forks);
		data->philos = NULL;
		data->forks = NULL;
		return (1);
	}
	data->start_time = get_timestamp_ms();
	data->simulation_end = 0;
	data->dead_flag = 0;
	data->full_philos = 0;
	if (init_philos(data))
		return (1);
	return (0);
}
