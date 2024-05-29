/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:11:34 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/29 23:39:48 by tchartie         ###   ########.fr       */
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

t_bool	take_fork(t_fork *forks, t_philo *philo)
{
	long	time;

	if (philo->first_fork->id == philo->second_fork->id)
		return (TRUE);
	handle_mutex(&forks->fork, LOCK);
	time = get_time(philo->table->time_start);
	write_status(FORK, philo, time);
	return (FALSE);
}

void	finish_eating(t_philo *philo)
{
	handle_mutex(&philo->table->table_mutex, LOCK);
	philo->nb_meal++;
	handle_mutex(&philo->table->table_mutex, UNLOCK);
	handle_mutex(&philo->first_fork->fork, UNLOCK);
	handle_mutex(&philo->second_fork->fork, UNLOCK);
}
