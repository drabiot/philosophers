/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:40:06 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/27 21:45:44 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	grab_arg(char *arg)
{
	int	value;

	if (is_int(arg))
	{
		value = ft_atol(arg);
		if (value > INT_MAX)
			error_msg("Error when creating arg. Values greater than INT_MAX.");
		else if (value < 0)
			error_msg("Error. You need to put positive values.");
		else
			return (value);
	}
	else
		error_msg("Error when creating arg. You need to put positive values.");
	return (-1);
}

void	parsing(t_data *arg, int argc, char **argv)
{
	arg->nb_philo = grab_arg(argv[1]);
	if (arg->nb_philo <= 0)
		return ;
	arg->time_die = grab_arg(argv[2]);
	if (arg->time_die == -1)
		return ;
	arg->time_eat = grab_arg(argv[3]);
	if (arg->time_eat == -1)
		return ;
	arg->time_sleep = grab_arg(argv[4]);
	if (arg->time_sleep == -1)
		return ;
	if (argc == 6)
	{
		arg->nb_eat = grab_arg(argv[5]);
		if (arg->nb_eat <= 0)
			arg->nb_eat = -2;
	}
	else
		arg->nb_eat = -1;
}
