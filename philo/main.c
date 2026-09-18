/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (!parse_args(argc, argv, &table))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (!init_table(&table))
	{
		printf("Error: initialization failed\n");
		cleanup_table(&table);
		return (1);
	}
	if (!run_simulation(&table))
	{
		printf("Error: could not create thread\n");
		cleanup_table(&table);
		return (1);
	}
	cleanup_table(&table);
	return (0);
}
