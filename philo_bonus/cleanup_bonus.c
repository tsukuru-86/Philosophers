/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	close_bonus(sem_t *semaphore)
{
	if (semaphore != SEM_FAILED)
		sem_close(semaphore);
}

void	cleanup_bonus(t_bonus *table)
{
	int	i;

	close_bonus(table->forks);
	close_bonus(table->room);
	close_bonus(table->print);
	close_bonus(table->death);
	close_bonus(table->start);
	close_bonus(table->ready);
	i = 0;
	while (i < table->meals_ready)
		close_bonus(table->meal[i++]);
	free(table->meal);
	free(table->pids);
}
