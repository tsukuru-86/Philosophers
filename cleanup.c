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

// cleanup.c

#include "philo.h"

void cleanup_simulation(t_data *data)
{
    int i;
    
    // フォークのミューテックスを破棄
    if (data->forks)
    {
        for (i = 0; i < data->num_philos; i++)
        {
            pthread_mutex_destroy(&data->forks[i]);
        }
        free(data->forks);
    }
    
    // 出力用ミューテックスを破棄
    pthread_mutex_destroy(&data->print_mutex);
    
    // 哲学者の配列を解放
    if (data->philos)
        free(data->philos);
}