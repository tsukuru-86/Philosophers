/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-17 09:09:45 by tsukuru           #+#    #+#             */
/*   Updated: 2025-06-17 09:09:45 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long long		last_meal_time;
	int				meals_eaten;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				someone_died;
	pthread_mutex_t	print_mutex;
	long long		start_time;
}	t_data;

// 関数プロトタイプ
int			parse_args(int argc, char **argv, t_data *data);
int			init_simulation(t_data *data);
int			start_simulation(t_data *data);
void		cleanup_simulation(t_data *data);
long long	get_time_ms(void);
void		print_status(t_philo *philo, char *status);
void		*philosopher_routine(void *arg);
void		precise_sleep(int ms);
int			check_philosopher_death(t_data *data, int i);

#endif