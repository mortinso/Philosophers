/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:53:11 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/17 18:32:13 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	logger(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->exit);
	if (!philo->table->dead_philo && !philo->table->all_satisfied)
		printf("%lld\t%i %s\n", elapsed_time(philo), philo->id + 1, str);
	pthread_mutex_unlock(&philo->table->exit);
}

int	grab_forks(t_philo *philo)
{
	philo->l_fork = philo->id;
	philo->r_fork = (philo->id + 1) % philo->table->num_philo;
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	else
		pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	logger(philo, "has taken a fork");
	if (philo->table->num_philo == 1)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
		return (1);
	}
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	else
		pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	logger(philo, "has taken a fork");
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eating);
	philo->last_meal = elapsed_time(philo);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->table->eating);
	logger(philo, "is eating");
	usleep(philo->table->tt_eat * 1000);
}

void	think(t_philo *philo)
{
	long long	tt_think;

	logger(philo, "is thinking");
	pthread_mutex_lock(&philo->table->eating);
	if (philo->n_meals == 0)
		tt_think = philo->table->tt_eat / 2;
	else
		tt_think = (philo->table->tt_die - (elapsed_time(philo) \
			- philo->last_meal)) / 2;
	pthread_mutex_unlock(&philo->table->eating);
	if (tt_think > philo->table->tt_eat)
		tt_think = philo->table->tt_eat;
	usleep(tt_think * 1000);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	if (philo->id % 2 == 0)
		think(philo);
	while (1)
	{
		if (grab_forks(philo))
			break ;
		eat(philo);
		pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
		if (check_exit(philo))
			break ;
		logger(philo, "is sleeping");
		usleep(philo->table->tt_sleep * 1000);
		if (check_exit(philo))
			break ;
		think(philo);
	}
	return (NULL);
}
