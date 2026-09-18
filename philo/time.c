/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	simulation_stopped(t_table *table)
{
	int	stopped;

	pthread_mutex_lock(&table->state_lock);
	stopped = table->stop;
	pthread_mutex_unlock(&table->state_lock);
	return (stopped);
}

void	set_simulation_stop(t_table *table)
{
	pthread_mutex_lock(&table->state_lock);
	table->stop = 1;
	pthread_mutex_unlock(&table->state_lock);
}

void	smart_sleep(t_table *table, long long duration)
{
	long long	end;
	long long	left;

	end = now_ms() + duration;
	while (!simulation_stopped(table))
	{
		left = end - now_ms();
		if (left <= 0)
			break ;
		if (left > 2)
			usleep(500);
		else
			usleep(100);
	}
}

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!simulation_stopped(philo->table))
		printf("%lld %d %s\n", now_ms() - philo->table->start_ms,
			philo->id, state);
	pthread_mutex_unlock(&philo->table->print_lock);
}
