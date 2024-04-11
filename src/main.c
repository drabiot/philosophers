/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:21:20 by tchartie          #+#    #+#             */
/*   Updated: 2024/04/11 22:01:19 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	arg;

	arg = (t_data){0};
	if (argc < 5 || argc > 6)
	{
		error_msg("Error. Too many or missing value");
		return (1);
	}
	parse_data(&arg, argc, argv);
	if (arg.nb_philo == -1 || arg.time_die == -1 || arg.time_eat == -1
		|| arg.time_sleep == -1 || arg.nb_eat == -1)
		return (1);
	return (0);
}
