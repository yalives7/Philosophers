/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 01:34:04 by sungor            #+#    #+#             */
/*   Updated: 2025/08/02 01:34:05 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		safe_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

static void	destroy_mutexes(t_data *data)
{
	safe_mutex_destroy(&data->print_mutex);
	safe_mutex_destroy(&data->death_mutex);
}

void	clean_up(t_data *data)
{
	if (data->forks)
	{
		destroy_forks(data);
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	destroy_mutexes(data);
}
