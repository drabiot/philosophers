/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:38:37 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/14 20:14:15 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	init_fork(t_data *table)
{
	int	i;
	int	ret;

	i = 0;
	while (i < table->nb_philo)
	{
		ret = handle_mutex(&table->forks[i].fork, INIT);
		if (ret != GOOD)
			return (FAILED);
		table->forks[i].id = i;
		i++;
	}
	return (GOOD);
}

static void	give_philo_forks(t_data *table, t_fork *fork, int pos)
{
	int	philo_nb;

	philo_nb = table->nb_philo;
	if (table->philos->id % 2 == 0)
	{
		table->philos->first_fork = &fork[pos];
		table->philos->second_fork = &fork[(pos + 1) % 2];
	}
	else
	{
		table->philos->first_fork = &fork[(pos + 1) % 2];
		table->philos->second_fork = &fork[pos];
	}
}

static int	init_philo(t_data *table)
{
	int	i;
	int	ret;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].id = i;
		table->philos[i].nb_meal = 0;
		table->philos[i].full_meal = FALSE;
		table->philos[i].last_meal = 0;
		ret = handle_mutex(&table->philos[i].philo, INIT);
		if (ret != GOOD)
			return (FAILED);
		give_philo_forks(table, table->forks, i);
		i++;
	}
	return (GOOD);
}

static void	thread_error(t_data *table)
{
	free(table->philos);
	free(table->forks);
}

void	data_init(t_data *table)
{
	int	ret;

	table->end = FALSE;
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!(table->philos))
		return ;
	table->forks = malloc(sizeof(t_fork) * table->nb_philo);
	if (!(table->forks))
	{
		free (table->philos);
		return ;
	}
	ret = init_fork(table);
	if (ret != GOOD)
	{
		thread_error(table);
		return ;
	}
	ret = init_philo(table);
	if (ret != GOOD)
	{
		thread_error(table);
		return ;
	}
}
