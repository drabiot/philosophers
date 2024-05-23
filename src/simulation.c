/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:36:55 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/23 18:29:02 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	write_status(t_state status, t_philo *philo, long time, long last_meal)
{
	if (handle_mutex(&philo->table->print, LOCK) == FAILED)
		return ;
	if (status == EAT && !(end_simulation(philo, last_meal, time)))
		printf(W"%ld"C" %d is eating\n"RST, time, philo->id);
	if (status == THINK && !(end_simulation(philo, last_meal, time)))
		printf(W"%ld"R" %d is thinking\n"RST, time, philo->id);
	if (status == SLEEP && !(end_simulation(philo, last_meal, time)))
		printf(W"%ld"G" %d is sleeping\n"RST, time, philo->id);
	if (status == DEAD)
		printf(W"%ld"M" %d died\n"RST, time, philo->id);
	handle_mutex(&philo->table->print, UNLOCK);
}

void	join_thread(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (handle_thread(&table->philos[i].philo_thread, JOIN, NULL, NULL)
			!= GOOD)
			return ;
		i++;
	}
}

void	simulation_init(t_data *table)
{
	int				i;
	struct timeval	time;

	i = 0;
	if (table->nb_philo == -1 || table->time_die == -1 || table->time_eat == -1
		|| table->time_sleep == -1 || table->nb_eat == -2)
		return ;
	gettimeofday(&time, NULL);
	table->time_start = time;
	while (i < table->nb_philo)
	{
		if (handle_thread(&table->philos[i].philo_thread, CREATE,
				start_dinner, &table->philos[i]) != GOOD)
			return ;
		i++;
	}
	join_thread(table);
}
