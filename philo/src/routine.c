/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:53:11 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/13 17:41:44 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	grab_forks(t_philo *philo)
{
	philo->r_fork = philo->id;
	philo->l_fork = (philo->id + 1) % philo->table->num_philo;
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	else
		pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	printf("%d has taken a fork\n", philo->id + 1);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	else
		pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	printf("%d has taken both forks\n", philo->id + 1);
}

void	eat(t_philo *philo)
{
	philo->last_meal = get_time();
	printf("%lld	%d is eating\n", get_time() - philo->table->time_start, \
		philo->id + 1);
	philo->n_meals++;
	usleep(philo->table->tt_eat);
	pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
	printf("%lld	%d is sleeping\n", get_time() - philo->table->time_start, \
		philo->id + 1);
	usleep(philo->table->tt_sleep);
	printf("%lld	%d is thinking\n", get_time() - philo->table->time_start, \
		philo->id + 1);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	while (1)
	{
		grab_forks(philo);
		eat(philo);
	}
	return (NULL);
}
