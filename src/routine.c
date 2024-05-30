/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:14:08 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/30 23:35:43 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_bool	eating(t_philo *philo, long *last_meal)
{
	long	time;
	t_bool	print;

	time = get_time(philo->table->time_start);
	print = TRUE;
	while (!end_simulation(philo))
	{
		if (print)
		{
			write_status(EAT, philo, time);
			print = FALSE;
			handle_mutex(&philo->table->table_mutex, LOCK);
			*last_meal = time;
			handle_mutex(&philo->table->table_mutex, UNLOCK);
		}
		if (time - *last_meal >= philo->table->time_eat)
		{
			finish_eating(philo);
			return (FALSE);
		}
		usleep(128);
		time = get_time(philo->table->time_start);
	}
	finish_eating(philo);
	return (TRUE);
}

static t_bool	sleeping(t_philo *philo)
{
	long	time;
	long	save;
	t_bool	print;

	time = get_time(philo->table->time_start);
	save = time;
	print = TRUE;
	while (!end_simulation(philo))
	{
		if (print)
		{
			write_status(SLEEP, philo, time);
			print = FALSE;
		}
		if (time - save >= philo->table->time_sleep)
			return (FALSE);
		usleep(128);
		time = get_time(philo->table->time_start);
	}
	return (TRUE);
}

static t_bool	thinking(t_philo *philo)
{
	long		time;

	time = get_time(philo->table->time_start);
	if (end_simulation(philo))
		return (TRUE);
	write_status(THINK, philo, time);
	usleep(128);
	if (take_fork(philo->first_fork, philo))
		return (TRUE);
	if (take_fork(philo->second_fork, philo))
		return (TRUE);
	if (philo->id == philo->table->nb_philo)
		change_fork(philo);
	return (FALSE);
}

void	*start_dinner(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	handle_mutex(&philo->table->table_mutex, LOCK);
	philo->last_meal = get_time(philo->table->time_start);
	handle_mutex(&philo->table->table_mutex, UNLOCK);
	if (philo->id % 2 == 0)
		usleep (128);
	while (philo->table->nb_eat == -1 || !full_up(philo->table))
	{
		if (thinking(philo))
			break ;
		if (eating(philo, &philo->last_meal))
			break ;
		if (sleeping(philo))
			break ;
		i++;
	}
	return (NULL);
}
