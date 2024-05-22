/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:23:11 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/22 18:09:50 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_time(struct timeval time_start)
{
	struct timeval	time;
	unsigned int	sec_diff;
	int				usec_diff;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	sec_diff = time.tv_sec - time_start.tv_sec;
	usec_diff = time.tv_usec - time_start.tv_usec;
	if (usec_diff < 0)
		usec_diff -= 1000;
	return (sec_diff * 1000 + usec_diff / 1000);
}
