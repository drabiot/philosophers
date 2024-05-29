/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:21:20 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/28 18:26:27 by tchartie         ###   ########.fr       */
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
	data_init(&table);
	if (table.philos && table.forks)
	{
		simulation_init(&table);
		free_mutex(&table);
		if (table.philos)
			free(table.philos);
		if (table.forks)
			free(table.forks);
	}
	return (0);
}
