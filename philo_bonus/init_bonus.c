/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static sem_t	*open_bonus(char *name, unsigned int value)
{
	sem_t	*semaphore;

	sem_unlink(name);
	semaphore = sem_open(name, O_CREAT | O_EXCL, 0600, value);
	if (semaphore != SEM_FAILED)
		sem_unlink(name);
	return (semaphore);
}

static void	reset_handles(t_bonus *table)
{
	table->forks = SEM_FAILED;
	table->room = SEM_FAILED;
	table->print = SEM_FAILED;
	table->death = SEM_FAILED;
	table->meal = NULL;
	table->start = SEM_FAILED;
	table->ready = SEM_FAILED;
	table->pids = NULL;
	table->created = 0;
	table->meals_ready = 0;
}

static void	meal_name(char *name, int number)
{
	char	digits[12];
	int		i;
	int		count;

	i = 0;
	while (MEAL_NAME[i])
	{
		name[i] = MEAL_NAME[i];
		i++;
	}
	count = 0;
	while (number > 0)
	{
		digits[count++] = number % 10 + '0';
		number /= 10;
	}
	while (count > 0)
		name[i++] = digits[--count];
	name[i] = '\0';
}

static int	open_meals(t_bonus *table)
{
	char	name[32];
	int		i;

	table->meal = malloc(sizeof(sem_t *) * table->count);
	if (!table->meal)
		return (0);
	i = 0;
	while (i < table->count)
	{
		meal_name(name, i + 1);
		table->meal[i] = open_bonus(name, 1);
		if (table->meal[i] == SEM_FAILED)
			return (0);
		table->meals_ready = ++i;
	}
	return (1);
}

int	init_bonus(t_bonus *table)
{
	reset_handles(table);
	table->pids = malloc(sizeof(pid_t) * table->count);
	if (!table->pids || !open_meals(table))
		return (0);
	table->forks = open_bonus(FORKS_NAME, table->count);
	table->room = open_bonus(ROOM_NAME, table->count - 1);
	table->print = open_bonus(PRINT_NAME, 1);
	table->death = open_bonus(DEATH_NAME, 1);
	table->start = open_bonus(START_NAME, 0);
	table->ready = open_bonus(READY_NAME, 0);
	if (table->forks == SEM_FAILED || table->room == SEM_FAILED
		|| table->print == SEM_FAILED || table->death == SEM_FAILED
		|| table->start == SEM_FAILED || table->ready == SEM_FAILED)
		return (0);
	return (1);
}
