/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by sungor            #+#    #+#             */
/*   Updated: 2025/08/02 01:56:01 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	print_error(const char *message)
{
	int	len;

	len = 0;
	while (message[len])
		len++;
	write(2, message, len);
	write(2, "\n", 1);
}

int	safe_mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		print_error("Error: Mutex initialization failed");
		return (1);
	}
	return (0);
}

int	safe_mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		print_error("Error: Mutex lock failed");
		return (1);
	}
	return (0);
}

int	safe_mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		print_error("Error: Mutex unlock failed");
		return (1);
	}
	return (0);
}

int	safe_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
	{
		print_error("Error: Mutex destroy failed");
		return (1);
	}
	return (0);
}
