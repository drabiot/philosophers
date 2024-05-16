/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:01:39 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/15 20:13:46 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	handle_error(int status)
{
	if (status == 0)
		return (GOOD);
	else
		return (FAILED);
}

int	handle_mutex(pthread_mutex_t *mutex, t_opcode opcode)
{
	int	ret;

	if (opcode == INIT)
		ret = handle_error(pthread_mutex_init(mutex, NULL));
	else if (opcode == DESTROY)
		ret = handle_error(pthread_mutex_destroy(mutex));
	else if (opcode == LOCK)
		ret = handle_error(pthread_mutex_lock(mutex));
	else if (opcode == UNLOCK)
		ret = handle_error(pthread_mutex_unlock(mutex));
	else
	{
		error_msg("Bad input, try <INIT>, <DESTROY>, <LOCK> or <UNLOCK>");
		return (BAD_INPUT);
	}
	if (ret == FAILED)
	{
		error_msg("Mutex failled");
		return (FAILED);
	}
	else
		return (GOOD);
}

int	handle_thread(pthread_t *thread, t_opcode opcode, void *(func)(void *),
	void *arg)
{
	int	ret;

	if (opcode == CREATE)
		ret = handle_error(pthread_create(thread, NULL, func, arg));
	else if (opcode == JOIN)
		ret = handle_error(pthread_join(*thread, NULL));
	else if (opcode == DETACH)
		ret = handle_error(pthread_detach(*thread));
	else
	{
		error_msg("Bad input, try <CREATE>, <JOIN> or <DETACH>");
		return (BAD_INPUT);
	}
	if (ret == FAILED)
	{
		error_msg("Mutex failled");
		return (FAILED);
	}
	else
		return (GOOD);
}
