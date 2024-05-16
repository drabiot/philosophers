/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:36:55 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/15 22:39:26 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	write_status(char *str, t_philo *philo)
{
	long		time;

	time = get_time() - philo->table->time_start;
	if (time >= 0 && time <= 2147483647)
	{
		printf("%ld ", time);
		printf("%d %s", philo->id, str);
	}
}

static void	eating(t_philo *philo)
{
	handle_mutex(&philo->first_fork->fork, LOCK);
	write_status("Take first Fork\n", philo);
	handle_mutex(&philo->second_fork->fork, LOCK);
	write_status("Take second Fork\n", philo);
	philo->nb_meal++;
	write_status("is eating\n", philo);
	ft_usleep(philo->table->time_eat);
	handle_mutex(&philo->first_fork->fork, UNLOCK);
	handle_mutex(&philo->second_fork->fork, UNLOCK);
}

static void	sleeping(t_philo *philo)
{
	write_status("is sleeping\n", philo);
	ft_usleep(philo->table->time_sleep);
}

static void	thinking(t_philo *philo)
{
	write_status("is thinking\n", philo);
}

static void	*start_simulation(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (i < 10)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		i++;
	}
	return (0);
}

void	simulation_init(t_data *table)
{
	int	i;

	i = 0;
	if (table->nb_philo == -1 || table->time_die == -1 || table->time_eat == -1
		|| table->time_sleep == -1 || table->nb_eat == -2)
		return ;
	else if (table->nb_philo == 1)
		return ;
		//TODO
	else
	{
		while (i < table->nb_philo)
		{
			handle_thread(&table->philos[i].philo_thread, CREATE,
				start_simulation, &table->philos[i]);
			i++;
		}
		table->time_start = get_time();
	}

}