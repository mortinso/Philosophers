/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:53:22 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/06 17:25:12 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
	{
		printf("Correct usage:	./philo <philos_number> <death_time> <eat_time> <sleep_time>\n");
		exit (1);
	}
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		exit (1);
	}
}
