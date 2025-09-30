/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:00:00 by sungor            #+#    #+#             */
/*   Updated: 2025/08/02 01:56:10 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if ((sign == 1 && result > 2147483647)
			|| (sign == -1 && result > 2147483648))
			return (-2);
		i++;
	}
	return ((int)(result * sign));
}

int	safe_thread_create(pthread_t *thread, void *(*routine)(void *), void *arg)
{
	if (pthread_create(thread, NULL, routine, arg) != 0)
	{
		print_error("Error: Thread creation failed");
		return (1);
	}
	return (0);
}

int	safe_thread_join(pthread_t thread)
{
	if (pthread_join(thread, NULL) != 0)
	{
		print_error("Error: Thread join failed");
		return (1);
	}
	return (0);
}
