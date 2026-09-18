/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_for_start(t_philo *philo)
{
	int	started;

	started = 0;
	while (!started)
	{
		pthread_mutex_lock(&philo->table->state_lock);
		started = philo->table->started;
		pthread_mutex_unlock(&philo->table->state_lock);
		if (!started)
			usleep(100);
	}
}

static int	wait_turn(t_philo *philo)
{
	long long	ticket;
	int			ready;

	pthread_mutex_lock(&philo->table->state_lock);
	ticket = philo->table->next_ticket++;
	pthread_mutex_unlock(&philo->table->state_lock);
	ready = 0;
	while (!ready && !simulation_stopped(philo->table))
	{
		pthread_mutex_lock(&philo->table->state_lock);
		ready = philo->table->serving_ticket == ticket;
		pthread_mutex_unlock(&philo->table->state_lock);
		if (!ready)
			usleep(100);
	}
	return (ready);
}

static int	take_forks(t_philo *philo)
{
	if (!wait_turn(philo))
		return (0);
	pthread_mutex_lock(philo->first_fork);
	print_state(philo, "has taken a fork");
	if (philo->table->count == 1)
	{
		pthread_mutex_lock(&philo->table->state_lock);
		philo->table->serving_ticket++;
		pthread_mutex_unlock(&philo->table->state_lock);
		while (!simulation_stopped(philo->table))
			usleep(200);
		pthread_mutex_unlock(philo->first_fork);
		return (0);
	}
	pthread_mutex_lock(philo->second_fork);
	pthread_mutex_lock(&philo->table->state_lock);
	philo->table->serving_ticket++;
	pthread_mutex_unlock(&philo->table->state_lock);
	print_state(philo, "has taken a fork");
	return (1);
}

static void	eat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = now_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	print_state(philo, "is eating");
	smart_sleep(philo->table, philo->table->eat_ms);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo);
	if (philo->id % 2 == 0)
		smart_sleep(philo->table, philo->table->eat_ms / 2);
	while (!simulation_stopped(philo->table))
	{
		if (!take_forks(philo))
			break ;
		eat_meal(philo);
		if (simulation_stopped(philo->table))
			break ;
		print_state(philo, "is sleeping");
		smart_sleep(philo->table, philo->table->sleep_ms);
		print_state(philo, "is thinking");
	}
	return (NULL);
}
