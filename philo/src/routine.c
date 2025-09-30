/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:41:20 by sungor            #+#    #+#             */
/*   Updated: 2025/07/28 23:41:21 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_single_philo_fork(t_philo *philo,
		pthread_mutex_t *first_fork)
{
	if (safe_mutex_lock(first_fork) != 0)
		return (0);
	print_philo_action(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		smart_sleep(philo->data->time_to_die * 2, philo->data);
		safe_mutex_unlock(first_fork);
		return (0);
	}
	return (1);
}

static int	grab_second_fork(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	if (safe_mutex_lock(second_fork) != 0)
	{
		safe_mutex_unlock(first_fork);
		return (0);
	}
	print_philo_action(philo, "has taken a fork");
	return (1);
}

int	grab_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (!handle_single_philo_fork(philo, first_fork))
		return (0);
	if (!grab_second_fork(philo, first_fork, second_fork))
		return (0);
	return (1);
}

void	release_forks(t_philo *philo)
{
	safe_mutex_unlock(philo->left_fork);
	safe_mutex_unlock(philo->right_fork);
}
