/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:28:03 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/30 23:16:41 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	thread_error(t_data *table)
{
	free(table->philos);
	free(table->forks);
}

void	error_msg(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write (2, &str[i], 1);
		i++;
	}
	write (2, "\n", 1);
}

void	free_mutex(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		handle_mutex(&table->forks[i].fork, DESTROY);
		i++;
	}
	handle_mutex(&table->print, DESTROY);
	handle_mutex(&table->table_mutex, DESTROY);
	handle_mutex(&table->death, DESTROY);
}
