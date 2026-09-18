/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	positive_bonus(char *str, int *value)
{
	long long	number;
	int			i;

	if (!str || !str[0])
		return (0);
	number = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		number = number * 10 + str[i++] - '0';
		if (number > INT_MAX)
			return (0);
	}
	if (number == 0)
		return (0);
	*value = (int)number;
	return (1);
}

int	parse_bonus(int argc, char **argv, t_bonus *table)
{
	int	time;

	if (argc != 5 && argc != 6)
		return (0);
	if (!positive_bonus(argv[1], &table->count)
		|| !positive_bonus(argv[2], &time))
		return (0);
	table->die_ms = time;
	if (!positive_bonus(argv[3], &time))
		return (0);
	table->eat_ms = time;
	if (!positive_bonus(argv[4], &time))
		return (0);
	table->sleep_ms = time;
	table->meal_limit = -1;
	if (argc == 6 && !positive_bonus(argv[5], &table->meal_limit))
		return (0);
	return (1);
}
