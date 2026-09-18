/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_table			*table;
}	t_philo;

struct s_table
{
	int				count;
	long long		die_ms;
	long long		eat_ms;
	long long		sleep_ms;
	int				meal_limit;
	long long		start_ms;
	int				stop;
	int				started;
	int				created;
	int				forks_ready;
	int				meals_ready;
	int				locks_ready;
	long long		next_ticket;
	long long		serving_ticket;
	pthread_mutex_t	*forks;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
};

int			parse_args(int argc, char **argv, t_table *table);
int			init_table(t_table *table);
void		cleanup_table(t_table *table);
int			run_simulation(t_table *table);
void		*philo_routine(void *arg);
void		monitor_philos(t_table *table);
int			simulation_stopped(t_table *table);
void		set_simulation_stop(t_table *table);
void		print_state(t_philo *philo, char *state);
long long	now_ms(void);
void		smart_sleep(t_table *table, long long duration);

#endif
