/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->count);
	if (!table->forks)
		return (0);
	i = 0;
	while (i < table->count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		table->forks_ready = ++i;
	}
	return (1);
}

static void	set_forks(t_table *table, t_philo *philo, int i)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	left = &table->forks[i];
	right = &table->forks[(i + 1) % table->count];
	if (i % 2 == 0)
	{
		philo->first_fork = left;
		philo->second_fork = right;
	}
	else
	{
		philo->first_fork = right;
		philo->second_fork = left;
	}
}

static int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->count);
	if (!table->philos)
		return (0);
	i = 0;
	while (i < table->count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		set_forks(table, &table->philos[i], i);
		if (pthread_mutex_init(&table->philos[i].meal_lock, NULL) != 0)
			return (0);
		table->meals_ready = ++i;
	}
	return (1);
}

int	init_table(t_table *table)
{
	table->forks = NULL;
	table->philos = NULL;
	table->forks_ready = 0;
	table->meals_ready = 0;
	table->created = 0;
	table->stop = 0;
	table->started = 0;
	table->next_ticket = 0;
	table->serving_ticket = 0;
	table->locks_ready = 0;
	if (pthread_mutex_init(&table->state_lock, NULL) != 0)
		return (0);
	table->locks_ready = 1;
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (0);
	table->locks_ready = 2;
	if (!init_forks(table) || !init_philos(table))
		return (0);
	return (1);
}
