/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:02:56 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/06 18:28:56 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *str)
{
	long int	num;
	int			neg;

	num = 0;
	neg = 1;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str)
	{
		num = (*str - '0') + (num * 10);
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	if ((num * neg > 2147483647) || (num * neg < -2147483648))
		return (-1);
	return (num * neg);
}
