/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_bonus	table;

	if (!parse_bonus(argc, argv, &table))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (!init_bonus(&table))
	{
		printf("Error: initialization failed\n");
		cleanup_bonus(&table);
		return (1);
	}
	if (!run_processes(&table))
	{
		printf("Error: could not create process\n");
		cleanup_bonus(&table);
		return (1);
	}
	cleanup_bonus(&table);
	return (0);
}
