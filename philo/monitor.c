/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_is_dead(t_philo *philo, long long now)
{
	long long	last_meal;

	pthread_mutex_lock(&philo->meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	return (now - last_meal >= philo->table->die_ms);
}

static int	philo_is_full(t_philo *philo)
{
	int	full;

	pthread_mutex_lock(&philo->meal_lock);
	full = philo->meals >= philo->table->meal_limit;
	pthread_mutex_unlock(&philo->meal_lock);
	return (full);
}

static void	announce_death(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_lock);
	pthread_mutex_lock(&table->state_lock);
	if (!table->stop)
	{
		table->stop = 1;
		printf("%lld %d died\n", now_ms() - table->start_ms, philo->id);
	}
	pthread_mutex_unlock(&table->state_lock);
	pthread_mutex_unlock(&table->print_lock);
}

void	monitor_philos(t_table *table)
{
	int			i;
	int			full;
	long long	now;

	while (!simulation_stopped(table))
	{
		i = 0;
		full = 0;
		now = now_ms();
		while (i < table->count)
		{
			if (philo_is_dead(&table->philos[i], now))
				return (announce_death(&table->philos[i]));
			if (table->meal_limit != -1 && philo_is_full(&table->philos[i]))
				full++;
			i++;
		}
		if (full == table->count)
			return (set_simulation_stop(table));
		usleep(200);
	}
}
