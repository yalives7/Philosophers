/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_timing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:00:00 by sungor            #+#    #+#             */
/*   Updated: 2025/08/03 15:00:00 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_eat_time(char **arg)
{
	int	time_to_eat;

	time_to_eat = ft_atoi(arg[3]);
	if (time_to_eat == -2)
	{
		print_error("Error: Time to eat out of integer range");
		return (1);
	}
	if (time_to_eat <= 0 || check_arg_content(arg[3]) == 1)
	{
		print_error("Error: Invalid time to eat (must be positive number)");
		return (1);
	}
	return (0);
}

static int	validate_sleep_time(char **arg)
{
	int	time_to_sleep;

	time_to_sleep = ft_atoi(arg[4]);
	if (time_to_sleep == -2)
	{
		print_error("Error: Time to sleep out of integer range");
		return (1);
	}
	if (time_to_sleep <= 0 || check_arg_content(arg[4]) == 1)
	{
		print_error("Error: Invalid time to sleep (must be positive number)");
		return (1);
	}
	return (0);
}

static int	validate_time_to_die(char **arg)
{
	int	time_to_die;

	time_to_die = ft_atoi(arg[2]);
	if (time_to_die == -2)
	{
		print_error("Error: Time to die out of integer range");
		return (1);
	}
	if (time_to_die <= 0 || check_arg_content(arg[2]) == 1)
	{
		print_error("Error: Invalid time to die (must be positive number)");
		return (1);
	}
	return (0);
}

int	validate_timing_args(char **arg)
{
	if (validate_time_to_die(arg))
		return (1);
	if (validate_eat_time(arg))
		return (1);
	if (validate_sleep_time(arg))
		return (1);
	return (0);
}
