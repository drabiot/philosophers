/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/23 20:27:15 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef char			t_bool;
typedef struct s_data	t_data;

# define FALSE 0
# define TRUE 1

# define INT_MAX 2147483647

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

typedef enum e_state
{
	DEAD,
	EAT,
	SLEEP,
	THINK,
}			t_state;

typedef struct s_fork
{
	int				id;
	t_bool			available;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo
{
	int				nb_philo;
	int				id;
	int				nb_meal;
	long			last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		philo_thread;
	t_data			*table;
	t_bool			full;
}					t_philo;

struct s_data
{
	int				nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nb_eat;
	struct timeval	time_start;
	t_bool			end;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	print;
	pthread_mutex_t	table_mutex;
};

# define RST    "\033[0m"
# define R		"\033[1;31m"
# define G      "\033[1;32m"
# define Y      "\033[1;33m"
# define B      "\033[1;34m"
# define M      "\033[1;35m"
# define C      "\033[1;36m"
# define W      "\033[1;37m" 

void	parsing(t_data *arg, int argc, char **argv);

long	ft_atol(const char *str);
t_bool	is_int(const char *str);

void	error_msg(const char *str);

void	data_init(t_data *table);
int		handle_mutex(pthread_mutex_t *mutex, t_opcode opcode);
int		handle_thread(pthread_t *thread, t_opcode opcode,
			void *(func)(void *), void *arg);

void	simulation_init(t_data *table);
long	get_time(struct timeval time);
void	ft_usleep(long ms, t_data *table);
void	write_status(t_state status, t_philo *philo, long time, long last_meal);

void	join_thread(t_data *table);
void	*start_dinner(void *arg);
t_bool	end_simulation(t_philo *philo, long last_meal, long time);
t_bool	take_fork(t_fork *forks, t_philo *philo, long last_meal);
void	finish_eating(t_philo *philo);
void	change_fork(t_philo *philo);
t_bool	full_up(t_data *table);

void	free_mutex(t_data *table);

#endif //PHILOSOPHERS_H
