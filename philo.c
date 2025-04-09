/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-07 00:57:07 by tsukuru           #+#    #+#             */
/*   Updated: 2025-04-07 00:57:07 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void precise_sleep(int ms)
{
    long long start;
    long long current;

    start = get_time_ms();
    while (1)
    {
        current = get_time_ms();
        if (current - start >= ms)
            break;
        usleep(500);
    }
}

void print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->someone_died)
    {
        printf("%lld %d %s\n", get_time_ms(), philo->id, status);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

int check_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (philo->data->someone_died)
    {
        pthread_mutex_unlock(&philo->data->print_mutex);
        return (1);
    }
    
    if (get_time_ms() - philo->last_meal_time > philo->data->time_to_die)
    {
        printf("%lld %d died\n", 
               get_time_ms() - philo->data->start_time, philo->id);
        philo->data->someone_died = 1;
        pthread_mutex_unlock(&philo->data->print_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
    return (0);
}

void eat(t_philo *philo)
{
    // フォークを取る
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork");
    
    // 1人の哲学者の場合は、ここで死ぬ
    if (philo->data->num_philos == 1)
    {
        precise_sleep(philo->data->time_to_die + 10);
        pthread_mutex_unlock(philo->right_fork);
        return;
    }
    
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork");
    
    // 食事
    print_status(philo, "is eating");
    pthread_mutex_lock(&philo->data->print_mutex);
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&philo->data->print_mutex);

    precise_sleep(philo->data->time_to_eat);

    // 食事回数のカウント
    philo->meals_eaten++;

    // フォークを戻す
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 != 0)
        usleep(1000);
    
    while (1)
    {
        if (check_death(philo))
            break;
    
        if (philo->data->must_eat_count != -1 && philo->meals_eaten >= philo->data->must_eat_count)
            break;
    
        eat(philo);
    
        if (check_death(philo))
            break;
    
        print_status(philo, "is sleeping");
        precise_sleep(philo->data->time_to_sleep);
    
        print_status(philo, "is sleeping");
        usleep(500);
    }
    return (NULL);
}