/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_bonus_forks(t_child *child)
{
	if (child->table->count == 1)
	{
		sem_wait(child->table->forks);
		print_bonus(child, "has taken a fork");
		while (1)
			usleep(1000);
	}
	sem_wait(child->table->room);
	sem_wait(child->table->forks);
	print_bonus(child, "has taken a fork");
	sem_wait(child->table->forks);
	print_bonus(child, "has taken a fork");
	sem_post(child->table->room);
}

static void	eat_bonus(t_child *child)
{
	sem_wait(child->table->meal[child->id - 1]);
	child->last_meal = now_bonus();
	sem_post(child->table->meal[child->id - 1]);
	print_bonus(child, "is eating");
	sleep_bonus(child->table->eat_ms);
	sem_wait(child->table->meal[child->id - 1]);
	child->meals++;
	sem_post(child->table->meal[child->id - 1]);
	sem_post(child->table->forks);
	sem_post(child->table->forks);
}

static int	finished_bonus(t_child *child)
{
	int	finished;

	if (child->table->meal_limit == -1)
		return (0);
	sem_wait(child->table->meal[child->id - 1]);
	finished = child->meals >= child->table->meal_limit;
	sem_post(child->table->meal[child->id - 1]);
	return (finished);
}

static void	run_child(t_child *child)
{
	if (child->id % 2 == 0)
		sleep_bonus(child->table->eat_ms / 2);
	while (1)
	{
		take_bonus_forks(child);
		eat_bonus(child);
		if (finished_bonus(child))
			exit(0);
		print_bonus(child, "is sleeping");
		sleep_bonus(child->table->sleep_ms);
		print_bonus(child, "is thinking");
	}
}

void	child_process(t_bonus *table, int id)
{
	t_child		child;
	pthread_t	monitor;

	child.id = id;
	child.meals = 0;
	child.table = table;
	sem_post(table->ready);
	sem_wait(table->start);
	child.start_ms = now_bonus();
	child.last_meal = child.start_ms;
	if (pthread_create(&monitor, NULL, death_monitor, &child) != 0)
		exit(2);
	if (pthread_detach(monitor) != 0)
		exit(2);
	run_child(&child);
}
