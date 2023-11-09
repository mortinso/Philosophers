/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:50:24 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/09 17:57:35 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_threads(t_table *table)
{
	int	index;

	index = 0;
	table->time_start = get_time();
	while (index < table->num_philo)
	{
		if (pthread_create(&table->threads[index], NULL, routine, \
			&table->philos[index]) != 0)
			return (1);
		index++;
	}
}

void	mutex_init(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->num_philo)
		pthread_mutex_init(&table->forks[index++], NULL);
}

void	table_var_init(t_table *table, char **argv, int argc)
{
	int	index;

	table->tt_die = ft_atoi(argv[2]) * 1000;
	table->tt_eat = ft_atoi(argv[3]) * 1000;
	table->tt_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		table->meal_cap = ft_atoi(argv[5]);
	// else
	// 	table->meal_cap = -1;
	index = 0;
	while (index < table->num_philo)
	{
		table->philos[index].table = table;
		table->philos[index].id = index;
		table->philos[index].last_meal = 0;
		table->philos[index].n_meals = 0;
		index++;
	}
}

t_table	*table_init(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->num_philo = ft_atoi(argv[1]);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philos)
		return (NULL);
	table_var_init(table, argv, argc);
	table->threads = malloc(sizeof(pthread_t) * table->num_philo);
	if (!table->threads)
		return (NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->forks)
		return (NULL);
	return (table);
}
