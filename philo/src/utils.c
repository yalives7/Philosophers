/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:41:40 by sungor            #+#    #+#             */
/*   Updated: 2025/07/28 23:41:41 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static long long	convert_timeval_to_ms(struct timeval tv)
{
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

long long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (convert_timeval_to_ms(tv));
}

void	smart_sleep(int duration_ms, t_data *data)
{
	long long	start_time;
	long long	current_time;
	long long	elapsed;

	if (duration_ms <= 0)
		return ;
	start_time = get_timestamp_ms();
	while (1)
	{
		if (data && has_simulation_ended(data))
			break ;
		current_time = get_timestamp_ms();
		elapsed = current_time - start_time;
		if (elapsed >= duration_ms)
			break ;
		usleep(500);
		if (data && has_simulation_ended(data))
			break ;
	}
}

int	has_simulation_ended(t_data *data)
{
	int	ended;

	safe_mutex_lock(&data->death_mutex);
	ended = data->simulation_end;
	safe_mutex_unlock(&data->death_mutex);
	return (ended);
}

void	print_philo_action(t_philo *philo, const char *status)
{
	long long	time_now;

	safe_mutex_lock(&philo->data->print_mutex);
	if (!has_simulation_ended(philo->data))
	{
		time_now = get_timestamp_ms() - philo->data->start_time;
		printf("%lld %d %s\n", time_now, philo->id, status);
	}
	safe_mutex_unlock(&philo->data->print_mutex);
}
