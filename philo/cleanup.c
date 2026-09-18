/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->meals_ready)
		pthread_mutex_destroy(&table->philos[i++].meal_lock);
	i = 0;
	while (i < table->forks_ready)
		pthread_mutex_destroy(&table->forks[i++]);
	free(table->philos);
	free(table->forks);
	if (table->locks_ready >= 2)
		pthread_mutex_destroy(&table->print_lock);
	if (table->locks_ready >= 1)
		pthread_mutex_destroy(&table->state_lock);
}
