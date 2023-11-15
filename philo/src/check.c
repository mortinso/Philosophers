/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:35:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/15 23:21:28 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*supervise(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	while (1)
	{
		if (check_starved(philo))
			break ;
		if (check_satisfied(philo))
			break ;
	}
	return (NULL);
}

int	check_starved(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->num_philo)
	{
		pthread_mutex_lock(&philo->table->eating);
		if (elapsed_time(philo) - philo[i].last_meal > philo->table->tt_die)
		{
			pthread_mutex_lock(&philo->table->exit);
			philo->table->dead_philo = 1;
			pthread_mutex_unlock(&philo->table->exit);
			printf("%lld\t%i died\n", elapsed_time(philo), philo[i].id + 1);
			pthread_mutex_unlock(&philo->table->eating);
			return (1);
		}
		pthread_mutex_unlock(&philo->table->eating);
		i++;
	}
	return (0);
}

int	check_satisfied(t_philo *philo)
{
	int	i;
	int	satisfied;

	if (!philo->table->meal_cap)
		return (0);
	i = 0;
	satisfied = 0;
	while (i < philo->table->num_philo)
	{
		pthread_mutex_lock(&philo->table->eating);
		if (philo[i].n_meals >= philo->table->meal_cap)
			satisfied++;
		pthread_mutex_unlock(&philo->table->eating);
		if (satisfied == philo->table->num_philo)
		{
			pthread_mutex_lock(&philo->table->exit);
			philo->table->all_satisfied = 1;
			pthread_mutex_unlock(&philo->table->exit);
			return (1);
		}
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
