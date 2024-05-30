/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:18:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/30 18:32:12 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_bool	end_simulation(t_philo *philo)
{
	handle_mutex(&philo->table->table_mutex, LOCK);
	if (philo->table->nb_eat != -1 && philo->nb_meal >= philo->table->nb_eat)
		philo->full = TRUE;
	handle_mutex(&philo->table->table_mutex, UNLOCK);
	handle_mutex(&philo->table->death, LOCK);
	if (philo->table->end == TRUE)
	{
		handle_mutex(&philo->table->death, UNLOCK);
		return (TRUE);
	}
	handle_mutex(&philo->table->death, UNLOCK);
	return (FALSE);
}

static void	set_end_philo(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (table->philos[i].dead == FALSE)
			table->philos[i].end = TRUE;
		i++;
	}
	handle_mutex(&table->death, LOCK);
	table->end = TRUE;
	handle_mutex(&table->death, UNLOCK);
}

t_bool	full_up(t_data *table)
{
	int	i;

	i = 0;
	handle_mutex(&table->table_mutex, LOCK);
	while (i < table->nb_philo)
	{
		if (table->philos[i].full == FALSE)
		{
			handle_mutex(&table->table_mutex, UNLOCK);
			return (FALSE);
		}
		i++;
	}
	handle_mutex(&table->table_mutex, UNLOCK);
	handle_mutex(&table->death, LOCK);
	table->end = TRUE;
	handle_mutex(&table->death, UNLOCK);
	set_end_philo(table);
	return (TRUE);
}

t_bool	supervise_philo(t_data *table)
{
	int		i;
	long	time;

	i = 0;
	time = get_time(table->time_start);
	while (i < table->nb_philo)
	{
		handle_mutex(&table->table_mutex, LOCK);
		if (time - table->philos[i].last_meal > table->time_die)
			table->philos[i].dead = TRUE;
		if (table->philos[i].dead == TRUE)
		{
			handle_mutex(&table->table_mutex, UNLOCK);
			handle_mutex(&table->print, LOCK);
			printf(W"%ld"M" %d died\n"RST, time, table->philos[i].id);
			handle_mutex(&table->print, UNLOCK);
			set_end_philo(table);
			return (FALSE);
		}
		handle_mutex(&table->table_mutex, UNLOCK);
		i++;
	}
	if (full_up(table))
		return (FALSE);
	return (TRUE);
}
