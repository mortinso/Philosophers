/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:35:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/06 18:27:20 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Checks if all the arguments are valid
void	verify_arguments(char **argv)
{
	int	index;

	index = 1;
	while (argv[index])
	{
		if (ft_atoi(argv[index]) <= 0)
		{
			printf("'%s': Numerical arguments are required\n", argv[index]);
			exit (1);
		}
		index++;
	}
}
