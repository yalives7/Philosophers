/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungor <sungor@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:41:56 by sungor            #+#    #+#             */
/*   Updated: 2025/08/02 01:55:12 by sungor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long long		last_meal;
	int				meals_eaten;
	int				is_eating;
	int				forks_taken;
	int				full_reported;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				simulation_end;
	int				dead_flag;
	int				full_philos;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}					t_data;

int					parse_args(int ac, char **av, t_data *data);
int					validate_arguments(char **arg);
int					validate_basic_args(char **arg);
int					validate_timing_args(char **arg);
int					check_arg_content(char *arg);
int					init_all(t_data *data);
void				start_simulation(t_data *data);
void				clean_up(t_data *data);
long long			get_timestamp_ms(void);
void				custom_usleep(int ms);
void				think(t_philo *philo);
void				take_forks(t_philo *philo);
void				eat(t_philo *philo);
void				sleep_philo(t_philo *philo);
void				print_action(t_philo *philo, char *msg);
int					simulation_has_ended(t_data *data);
void				*philosopher_routine(void *arg);
void				perform_routine(t_philo *philo);
void				smart_sleep(int duration_ms, t_data *data);
int					has_simulation_ended(t_data *data);
void				print_philo_action(t_philo *philo, const char *status);
void				*monitor_routine(void *arg);
int					grab_forks(t_philo *philo);
void				release_forks(t_philo *philo);

int					safe_mutex_init(pthread_mutex_t *mutex);
int					safe_mutex_lock(pthread_mutex_t *mutex);
int					safe_mutex_unlock(pthread_mutex_t *mutex);
int					safe_mutex_destroy(pthread_mutex_t *mutex);

void				print_error(const char *message);

int					ft_atoi(const char *str);
int					safe_thread_create(pthread_t *thread,
						void *(*routine)(void *), void *arg);
int					safe_thread_join(pthread_t thread);

#endif
