/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:08:54 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/29 22:57:08 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ret > INT_MAX)
			return (-10);
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}

t_bool	is_int(const char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 10)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (0);
	else
		return (1);
}
