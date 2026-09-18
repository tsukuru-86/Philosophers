/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_threads(t_table *table)
{
	int	i;

	table->start_ms = now_ms();
	i = 0;
	while (i < table->count)
	{
		pthread_mutex_lock(&table->philos[i].meal_lock);
		table->philos[i].last_meal = table->start_ms;
		pthread_mutex_unlock(&table->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_lock(&table->state_lock);
	table->started = 1;
	pthread_mutex_unlock(&table->state_lock);
}

static void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->created)
		pthread_join(table->philos[i++].thread, NULL);
}

int	run_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_routine, &table->philos[i]) != 0)
		{
			set_simulation_stop(table);
			pthread_mutex_lock(&table->state_lock);
			table->started = 1;
			pthread_mutex_unlock(&table->state_lock);
			join_threads(table);
			return (0);
		}
		table->created = ++i;
	}
	start_threads(table);
	monitor_philos(table);
	join_threads(table);
	return (1);
}
