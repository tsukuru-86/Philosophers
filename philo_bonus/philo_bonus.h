/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define FORKS_NAME "/philo_forks"
# define ROOM_NAME "/philo_room"
# define PRINT_NAME "/philo_print"
# define DEATH_NAME "/philo_death"
# define MEAL_NAME "/philo_meal_"
# define START_NAME "/philo_start"
# define READY_NAME "/philo_ready"

typedef struct s_bonus
{
	int			count;
	long long	die_ms;
	long long	eat_ms;
	long long	sleep_ms;
	int			meal_limit;
	pid_t		*pids;
	int			created;
	int			meals_ready;
	sem_t		*forks;
	sem_t		*room;
	sem_t		*print;
	sem_t		*death;
	sem_t		**meal;
	sem_t		*start;
	sem_t		*ready;
}	t_bonus;

typedef struct s_child
{
	int			id;
	int			meals;
	long long	last_meal;
	long long	start_ms;
	t_bonus		*table;
}	t_child;

int			parse_bonus(int argc, char **argv, t_bonus *table);
int			init_bonus(t_bonus *table);
void		cleanup_bonus(t_bonus *table);
int			run_processes(t_bonus *table);
void		child_process(t_bonus *table, int id);
void		*death_monitor(void *arg);
void		print_bonus(t_child *child, char *state);
void		print_death(t_child *child);
long long	now_bonus(void);
void		sleep_bonus(long long duration);

#endif
