/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_basic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:00:00 by sungor            #+#    #+#             */
/*   Updated: 2025/08/03 15:00:00 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_philosopher_count(char **arg)
{
	int	philo_count;

	philo_count = ft_atoi(arg[1]);
	if (philo_count == -2)
	{
		print_error("Error: Number of philosophers out of integer range");
		return (1);
	}
	if (philo_count <= 0 || check_arg_content(arg[1]) == 1)
	{
		print_error("Error: Invalid number of philosophers"
			" (must be positive number)");
		return (1);
	}
	return (0);
}

static int	validate_must_eat_count(char **arg)
{
	int	must_eat_count;

	if (!arg[5])
		return (0);
	must_eat_count = ft_atoi(arg[5]);
	if (must_eat_count == -2)
	{
		print_error("Error: Must eat count out of integer range");
		return (1);
	}
	if (must_eat_count <= 0 || check_arg_content(arg[5]) == 1)
	{
		print_error("Error: Invalid must_eat_count (must be positive number)");
		return (1);
	}
	return (0);
}

int	validate_basic_args(char **arg)
{
	if (validate_philosopher_count(arg))
		return (1);
	if (validate_must_eat_count(arg))
		return (1);
	return (0);
}
