/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:53:22 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/06 18:30:37 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	if (argc == 1)
		printf("Correct usage:	./philo <philos_number> <death_time> <eat_time> <sleep_time>\n");
	else if (argc < 5 || argc > 6)
		printf("Wrong number of arguments\n");
	if (argc == 1 || argc < 5 || argc > 6)
		exit (1);
	verify_arguments(argv);
	table = table_init(argc, argv);
	free(table);
}
