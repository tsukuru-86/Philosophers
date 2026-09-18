/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static long long	read_last_meal(t_child *child)
{
	long long	last;

	sem_wait(child->table->meal[child->id - 1]);
	last = child->last_meal;
	sem_post(child->table->meal[child->id - 1]);
	return (last);
}

static int	confirm_death(t_child *child)
{
	long long	last;

	sem_wait(child->table->death);
	last = read_last_meal(child);
	if (now_bonus() - last >= child->table->die_ms)
	{
		print_death(child);
		exit(1);
	}
	sem_post(child->table->death);
	return (0);
}

void	*death_monitor(void *arg)
{
	t_child	*child;

	child = (t_child *)arg;
	while (1)
	{
		if (now_bonus() - read_last_meal(child) >= child->table->die_ms)
			confirm_death(child);
		usleep(200);
	}
	return (NULL);
}
