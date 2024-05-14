/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:21:20 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/14 19:58:20 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	table;

	table = (t_data){0};
	if (argc < 5 || argc > 6)
	{
		error_msg("Error. Too many or missing value");
		return (1);
	}
	parsing(&table, argc, argv);
	/*if (arg.nb_philo == -1 || arg.time_die == -1 || arg.time_eat == -1
		|| arg.time_sleep == -1)
		return (1);*/
	data_init(&table);
	// exec
	if (table.philos)
		free(table.philos);
	if (table.forks)
		free(table.forks);
	return (0);
}
