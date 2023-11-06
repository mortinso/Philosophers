/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:50:24 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/06 18:15:37 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_table	*table_init(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->num_philo = ft_atoi(argv[1]);
	table->tt_die = ft_atoi(argv[2]);
	table->tt_eat = ft_atoi(argv[3]);
	table->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->min_eat = ft_atoi(argv[5]);
	return (table);
}
