/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:00:00 by tsukuru           #+#    #+#             */
/*   Updated: 2026/09/18 15:00:00 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	append_number(char *buffer, int index, long long number)
{
	char	digits[20];
	int		count;

	count = 0;
	if (number == 0)
		buffer[index++] = '0';
	while (number > 0)
	{
		digits[count++] = number % 10 + '0';
		number /= 10;
	}
	while (count > 0)
		buffer[index++] = digits[--count];
	return (index);
}

static int	append_text(char *buffer, int index, char *text)
{
	int	i;

	i = 0;
	while (text[i])
		buffer[index++] = text[i++];
	return (index);
}

static void	write_line(t_child *child, char *state)
{
	char	buffer[128];
	int		length;

	length = append_number(buffer, 0, now_bonus() - child->start_ms);
	buffer[length++] = ' ';
	length = append_number(buffer, length, child->id);
	buffer[length++] = ' ';
	length = append_text(buffer, length, state);
	buffer[length++] = '\n';
	write(1, buffer, length);
}

void	print_bonus(t_child *child, char *state)
{
	sem_wait(child->table->death);
	sem_wait(child->table->print);
	write_line(child, state);
	sem_post(child->table->print);
	sem_post(child->table->death);
}

void	print_death(t_child *child)
{
	sem_wait(child->table->print);
	write_line(child, "died");
	sem_post(child->table->print);
}
