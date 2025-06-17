/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-07 09:45:28 by tsukuru           #+#    #+#             */
/*   Updated: 2025-04-07 09:45:28 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_simulation(t_data *data)
{
	int	i;

	i = 0;
	// フォークのミューテックスを破棄
	if (data->forks)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	// 出力用ミューテックスを破棄
	pthread_mutex_destroy(&data->print_mutex);
	// 哲学者の配列を解放する
	if (data->philos)
		free(data->philos);
}
