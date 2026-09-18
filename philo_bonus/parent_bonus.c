/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	mark_reaped(t_bonus *table, pid_t pid)
{
	int	i;

	i = 0;
	while (i < table->created)
	{
		if (table->pids[i] == pid)
			table->pids[i] = -1;
		i++;
	}
}

static void	stop_children(t_bonus *table, int reaped)
{
	int	i;
	int	status;

	i = 0;
	while (i < table->created)
	{
		if (table->pids[i] > 0)
			kill(table->pids[i], SIGTERM);
		i++;
	}
	while (reaped < table->created)
	{
		if (waitpid(-1, &status, 0) > 0)
			reaped++;
		else
			break ;
	}
}

static int	supervise_children(t_bonus *table)
{
	int		status;
	int		reaped;
	pid_t	pid;

	reaped = 0;
	while (reaped < table->created)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			return (stop_children(table, reaped), 0);
		reaped++;
		mark_reaped(table, pid);
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		{
			stop_children(table, reaped);
			return (1);
		}
	}
	return (1);
}

static void	release_children(t_bonus *table)
{
	int	i;

	i = 0;
	while (i++ < table->count)
		sem_wait(table->ready);
	i = 0;
	while (i++ < table->count)
		sem_post(table->start);
}

int	run_processes(t_bonus *table)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < table->count)
	{
		pid = fork();
		if (pid < 0)
			return (stop_children(table, 0), 0);
		if (pid == 0)
			child_process(table, i + 1);
		table->pids[i] = pid;
		table->created = ++i;
	}
	release_children(table);
	return (supervise_children(table));
}
