/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:41:31 by sungor            #+#    #+#             */
/*   Updated: 2025/07/28 23:41:32 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (safe_thread_create(&data->philos[i].thread, philosopher_routine,
				&data->philos[i]) != 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		safe_thread_join(data->philos[i].thread);
		i++;
	}
}

void	start_simulation(t_data *data)
{
	pthread_t	monitor;

	if (safe_thread_create(&monitor, monitor_routine, data) != 0)
	{
		return ;
	}
	if (create_threads(data) != 0)
		return ;
	join_threads(data);
	safe_thread_join(monitor);
}
