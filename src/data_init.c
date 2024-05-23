/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:38:37 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/23 19:20:49 by tchartie         ###   ########.fr       */
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
		table->forks[i].id = i + 1;
		table->forks[i].available = TRUE;
		i++;
	}
	return (GOOD);
}

static void	give_philo_forks(t_data *table, t_fork *fork, int pos)
{
	int	philo_nb;

	philo_nb = table->nb_philo;
	table->philos[pos].first_fork = &fork[(pos + 1) % philo_nb];
	table->philos[pos].second_fork = &fork[pos];
	if (table->philos[pos].id % 2 != 0)
	{
		table->philos[pos].first_fork = &fork[pos];
		table->philos[pos].second_fork = &fork[(pos + 1) % philo_nb];
	}
}

static int	init_philo(t_data *table)
{
	int	i;
	int	ret;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].nb_philo = table->nb_philo;
		table->philos[i].id = i + 1;
		table->philos[i].nb_meal = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		table->philos[i].full = FALSE;
		ret = handle_mutex(&table->print, INIT);
		if (ret != GOOD)
			return (FAILED);
		ret = handle_mutex(&table->table_mutex, INIT);
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
