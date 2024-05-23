/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:18:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/23 20:34:56 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	change_fork(t_philo *philo)
{
	t_fork	*tmp;

	tmp = philo->first_fork;
	philo->first_fork = philo->second_fork;
	philo->second_fork = tmp;
}

t_bool	take_fork(t_fork *forks, t_philo *philo, long last_meal)
{
	long	time;

	time = get_time(philo->table->time_start);
	if (end_simulation(philo, last_meal, time))
		return (TRUE);
	handle_mutex(&forks->fork, LOCK);
	while (forks->available == FALSE)
	{
		handle_mutex(&forks->fork, UNLOCK);
		usleep(128);
		time = get_time(philo->table->time_start);
		if (end_simulation(philo, last_meal, time))
			return (TRUE);
		handle_mutex(&forks->fork, LOCK);
	}
	forks->available = FALSE;
	handle_mutex(&forks->fork, UNLOCK);
	return (FALSE);
}

void	finish_eating(t_philo *philo)
{
	handle_mutex(&philo->table->table_mutex, LOCK);
	philo->nb_meal++;
	handle_mutex(&philo->first_fork->fork, LOCK);
	philo->first_fork->available = TRUE;
	handle_mutex(&philo->first_fork->fork, UNLOCK);
	handle_mutex(&philo->second_fork->fork, LOCK);
	philo->second_fork->available = TRUE;
	handle_mutex(&philo->second_fork->fork, UNLOCK);
	handle_mutex(&philo->table->table_mutex, UNLOCK);
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
	table->end = TRUE;
	handle_mutex(&table->table_mutex, UNLOCK);
	return (TRUE);
}

t_bool	end_simulation(t_philo *philo, long last_meal, long time)
{
	int	i;

	i = 0;
	handle_mutex(&philo->table->table_mutex, LOCK);
	if (philo->table->nb_eat != -1 && philo->nb_meal >= philo->table->nb_eat)
		philo->full = TRUE;
	if (philo->table->end == TRUE)
	{
		handle_mutex(&philo->table->table_mutex, UNLOCK);
		return (TRUE);
	}
	if (get_time(philo->table->time_start) - last_meal > philo->table->time_die)
	{
		philo->table->end = TRUE;
		write_status(DEAD, philo, time, last_meal);
		handle_mutex(&philo->table->table_mutex, UNLOCK);
		return (TRUE);
	}
	else
	{
		handle_mutex(&philo->table->table_mutex, UNLOCK);
		return (FALSE);
	}
}
