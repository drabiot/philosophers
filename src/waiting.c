/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:18:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/22 19:29:28 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
		usleep(50);
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
	handle_mutex(&philo->first_fork->fork, LOCK);
	philo->first_fork->available = TRUE;
	handle_mutex(&philo->first_fork->fork, UNLOCK);
	handle_mutex(&philo->second_fork->fork, LOCK);
	philo->second_fork->available = TRUE;
	handle_mutex(&philo->second_fork->fork, UNLOCK);
}

t_bool	end_simulation(t_philo *philo, long last_meal, long time)
{
	int	i;

	i = 0;
	if (philo->table->end == TRUE)
		return (TRUE);
	if (get_time(philo->table->time_start) - last_meal > philo->table->time_die)
	{
		philo->table->end = TRUE;
		write_status(DEAD, philo, time, last_meal);
		return (TRUE);
	}
	else
		return (FALSE);
}
