/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:41:25 by sungor            #+#    #+#             */
/*   Updated: 2025/07/28 23:41:26 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	eat_meal(t_philo *philo)
{
	safe_mutex_lock(&philo->data->death_mutex);
	philo->is_eating = 1;
	philo->last_meal = get_timestamp_ms();
	safe_mutex_unlock(&philo->data->death_mutex);
	print_philo_action(philo, "is eating");
	safe_mutex_lock(&philo->data->death_mutex);
	philo->meals_eaten++;
	safe_mutex_unlock(&philo->data->death_mutex);
	smart_sleep(philo->data->time_to_eat, philo->data);
	safe_mutex_lock(&philo->data->death_mutex);
	philo->is_eating = 0;
	safe_mutex_unlock(&philo->data->death_mutex);
}

static int	check_meal_count(t_philo *philo)
{
	int	should_exit;

	safe_mutex_lock(&philo->data->death_mutex);
	should_exit = 0;
	if (philo->data->must_eat_count > 0
		&& philo->meals_eaten >= philo->data->must_eat_count)
		should_exit = 1;
	safe_mutex_unlock(&philo->data->death_mutex);
	return (should_exit);
}

static void	handle_single_philosopher(t_philo *philo)
{
	grab_forks(philo);
}

static void	philosopher_cycle(t_philo *philo)
{
	if (has_simulation_ended(philo->data))
		return ;
	if (!grab_forks(philo))
		return ;
	eat_meal(philo);
	release_forks(philo);
	if (check_meal_count(philo) || has_simulation_ended(philo->data))
		return ;
	print_philo_action(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
	if (has_simulation_ended(philo->data))
		return ;
	print_philo_action(philo, "is thinking");
	if (philo->data->num_philos % 2 == 1)
		usleep(500);
}

void	perform_routine(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		handle_single_philosopher(philo);
		return ;
	}
	if (philo->id % 2 == 0)
		smart_sleep(philo->data->time_to_eat / 2, philo->data);
	while (!has_simulation_ended(philo->data))
	{
		philosopher_cycle(philo);
		if (check_meal_count(philo) || has_simulation_ended(philo->data))
			break ;
		usleep(50);
	}
}
