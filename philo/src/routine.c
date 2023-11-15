/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:53:11 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/15 23:23:16 by mortins-         ###   ########.fr       */
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
	philo->r_fork = philo->id;
	philo->l_fork = (philo->id + 1) % philo->table->num_philo;
	pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	logger(philo, "has taken a fork");
	if (philo->table->num_philo == 1)
		return (1);
	pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	logger(philo, "has taken a fork");
	return (0);
}

void	eat(t_philo *philo)
{
	logger(philo, "is eating");
	pthread_mutex_lock(&philo->table->eating);
	philo->last_meal = elapsed_time(philo);
	pthread_mutex_unlock(&philo->table->eating);
	usleep(philo->table->tt_eat * 1000);
	pthread_mutex_lock(&philo->table->eating);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->table->eating);
}

void	think(t_philo *philo)
{
	long long	tt_think;

	if (elapsed_time(philo) < 10)
		tt_think = 20;
	else
		tt_think = philo->table->tt_die - elapsed_time(philo) \
			- philo->last_meal - philo->table->tt_eat;
	if (tt_think < 0)
		tt_think = 0;
	else if (tt_think == 0)
		tt_think = 1;
	else if (tt_think > 600)
		tt_think = 200;
	logger(philo, "is thinking");
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
		pthread_mutex_lock(&philo->table->exit);
		if (philo->table->dead_philo || philo->table->all_satisfied)
		{
			pthread_mutex_unlock(&philo->table->exit);
			break ;
		}
		pthread_mutex_unlock(&philo->table->exit);
		logger(philo, "is sleeping");
		usleep(philo->table->tt_sleep * 1000);
		think(philo);
	}
	return (NULL);
}
