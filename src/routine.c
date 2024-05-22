/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:14:08 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/22 19:29:15 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_bool	eating(t_philo *philo, long *last_meal)
{
	long	time;
	t_bool	print;

	time = get_time(philo->table->time_start);
	print = TRUE;
	while (!end_simulation(philo, *last_meal, time))
	{
		if (print)
		{
			write_status(EAT, philo, time, *last_meal);
			print = FALSE;
			*last_meal = time;
		}
		if (time - *last_meal >= philo->table->time_eat)
		{
			finish_eating(philo);
			return (FALSE);
		}
		usleep(philo->table->time_eat);
		time = get_time(philo->table->time_start);
	}
	return (TRUE);
}

static t_bool	sleeping(t_philo *philo, long last_meal)
{
	long	time;
	long	save;
	t_bool	print;

	time = get_time(philo->table->time_start);
	save = time;
	print = TRUE;
	while (!end_simulation(philo, last_meal, time))
	{
		if (print)
		{
			write_status(SLEEP, philo, time, last_meal);
			print = FALSE;
		}
		if (time - save >= philo->table->time_sleep)
			return (FALSE);
		usleep(philo->table->time_sleep);
		time = get_time(philo->table->time_start);
	}
	return (TRUE);
}

static t_bool	thinking(t_philo *philo, long last_meal)
{
	long	time;

	time = get_time(philo->table->time_start);
	if (end_simulation(philo, last_meal, time))
		return (TRUE);
	write_status(THINK, philo, time, last_meal);
	if (take_fork(philo->first_fork, philo, last_meal))
		return (TRUE);
	if (take_fork(philo->second_fork, philo, last_meal))
		return (TRUE);
	return (FALSE);
}

void	*start_dinner(void *arg)
{
	t_philo	*philo;
	long	last;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	philo->last_meal = get_time(philo->table->time_start);
	last = philo->last_meal;
	while (i < 10)
	{
		if (thinking(philo, last))
			break ;
		if (eating(philo, &last))
			break ;
		if (sleeping(philo, last))
			break ;
		i++;
	}
	return (NULL);
}
