/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:41:48 by sungor            #+#    #+#             */
/*   Updated: 2025/08/02 01:57:18 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_content(char *arg)
{
	int	i;

	if (!arg || arg[0] == '\0')
		return (1);
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	validate_arguments(char **arg)
{
	if (validate_basic_args(arg))
		return (1);
	if (validate_timing_args(arg))
		return (1);
	return (0);
}
