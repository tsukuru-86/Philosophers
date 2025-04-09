/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-07 04:25:38 by tsukuru           #+#    #+#             */
/*   Updated: 2025-04-07 04:25:38 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int all_ate_enough(t_data *data)
{
    int i;
    int done;

    if (data->must_eat_count == -1)
        return (0);

    done = 1;
    i = 0;
    while (data->num_philos)
    {
        if (data->philos[i].meals_eaten <data->must_eat_count)
        {
            done = 0;
            break;
        }
        i++;
    }

    return (done);

}

// 哲学者の死亡監視
void *monitor_routine(void *arg)
{
    t_data *data;
    int i;
    
    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        while(i < data->num_philos)
        {
            pthread_mutex_lock(&data->print_mutex);
            
            // 既に誰かが死んでいたら終了
            if (data->someone_died)
            {
                pthread_mutex_unlock(&data->print_mutex);
                return (NULL);
            }
            
            // 食事からの経過時間をチェック
            if (get_time_ms() - data->philos[i].last_meal_time > data->time_to_die)
            {
                printf("%lld %d died\n", 
                       get_time_ms() - data->start_time, data->philos[i].id);
                data->someone_died = 1;
                pthread_mutex_unlock(&data->print_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->print_mutex);
            i++;
        }
        
        // 全員が十分食べたかチェック
        if (all_ate_enough(data))
            return (NULL);
        
        // 少し待機して、CPU使用率を下げる
        usleep(1000);
    }
    
    return (NULL);
}

int start_simulation(t_data *data)
{
    int i;
    pthread_t monitor;

    data->start_time = get_time_ms();

    i = 0;

    while (i < data->num_philos)
    {
        data->philos[i].last_meal_time = data->start_time;
        if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine, &data->philos[i]) != 0)
            return (0);
        i++;
    }

    if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
        return (0);

    pthread_join(monitor, NULL);

    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
    return (1);
}