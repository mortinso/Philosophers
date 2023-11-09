/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:53:22 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/09 18:03:57 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_join(table->threads[i++], NULL) != 0)
			return (1);
	}
}

void	free_table(t_table *table)
{
	free(table->philos);
	free(table->forks);
	free(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc == 1)
		return (printf("Correct usage:	./philo <philos_number> <death_time>" \
			" <eat_time> <sleep_time>\n"));
	else if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"));
	verify_arguments(argv);
	table = table_init(argc, argv);
	if (!table)
		return (1);
	mutex_init(table);
	if (create_threads(table))
		return (1);
	if (join_threads(table))
		return (1);
	free_table(table);
}
