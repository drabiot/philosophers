/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/04/11 22:05:01 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>

typedef char	t_bool;

# define FALSE 0
# define TRUE 1

# define INT_MAX 2147483647

typedef struct s_data
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_eat;
}		t_data;

void	parse_data(t_data *arg, int argc, char **argv);

long	ft_atol(const char *str);
t_bool	is_int(const char *str);

void	error_msg(const char *str);

#endif //PHILOSOPHERS_H
