/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/15 22:36:01 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef char	t_bool;
typedef struct	s_data	t_data;

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
	int				nb_philo;
	int				id;
	int				nb_meal;
	t_bool			full_meal;
	long			last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		philo_thread;
	pthread_mutex_t	philo_mutex;
	t_data			*table;
}					t_philo;

struct s_data
{
	int		nb_philo;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		nb_eat;
	long	time_start;
	t_bool	end;
	t_fork	*forks;
	t_philo	*philos;
};

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
int		handle_thread(pthread_t *thread, t_opcode opcode,
			void *(func)(void *), void *arg);

void 	simulation_init(t_data *table);
long	get_time();
void	ft_usleep(long ms);

#endif //PHILOSOPHERS_H
