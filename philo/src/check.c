/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:35:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/14 17:17:09 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*supervise(void *var)
{
	t_philo	*philos;

	philos = (t_philo *)var;
	while (1)
	{
		if (check_starved(philos))
			break;
	}
	return (NULL);
}

int	check_starved(t_philo *philos)
{
	int	i;

	i = 0;
	while(i < philos->table->num_philo)
	{
		pthread_mutex_lock(&philos->table->eating);
		if (get_time() - philos->table->time_start - philos[i].last_meal > (philos->table->tt_die / 1000))
		{
			pthread_mutex_lock(&philos->table->exit);
			philos->table->dead_philo = 1;
			pthread_mutex_unlock(&philos->table->exit);
			printf("%lld\t%d died\n", get_time() - philos->table->time_start, philos[i].id + 1);
			pthread_mutex_unlock(&philos->table->eating);
			return (1);
		}
		pthread_mutex_unlock(&philos->table->eating);
		i++;
	}
	return (0);
}

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
