/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/14 20:16:04 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef char	t_bool;

# define FALSE 0
# define TRUE 1

# define INT_MAX 2147483647

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				nb_meal;
	t_bool			full_meal;
	long			last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	philo;
}					t_philo;

typedef struct s_data
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nb_eat;
	long	time_start;
	t_bool	end;
	t_fork	*forks;
	t_philo	*philos;
}			t_data;

typedef enum e_opcode
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

typedef enum e_error
{
	GOOD,
	BAD_INPUT,
	FAILED,
}			t_error;

void	parsing(t_data *arg, int argc, char **argv);

long	ft_atol(const char *str);
t_bool	is_int(const char *str);

void	error_msg(const char *str);

void	data_init(t_data *table);
int		handle_mutex(pthread_mutex_t *mutex, t_opcode opcode);

#endif //PHILOSOPHERS_H
