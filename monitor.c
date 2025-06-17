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

int	all_ate_enough(t_data *data)
{
	int	i;
	int	done;

	if (data->must_eat_count == -1)
		return (0);
	done = 1;
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat_count)
		{
			done = 0;
			break ;
		}
		i++;
	}
	return (done);
}

int	check_philosopher_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->print_mutex);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	if (get_time_ms() - data->philos[i].last_meal_time > data->time_to_die)
	{
		printf("%lld %d died\n",
			get_time_ms() - data->start_time, data->philos[i].id);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
			i++;
		}
		if (all_ate_enough(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time_ms();
	if (!create_threads(data))
		return (0);
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
