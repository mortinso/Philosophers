/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:53:11 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/14 18:23:53 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	logger(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->exit);
	if (!philo->table->dead_philo && !philo->table->all_satisfied)
	{
		printf("%lld\t%d %s\n", get_time() - philo->table->time_start, \
		philo->id + 1, str);
	}
	pthread_mutex_unlock(&philo->table->exit);
}

// void	ft_usleep(long long time)
// {
// 	long long	start;

// 	start = get_time();
// 	while (get_time() < start + (time / 1000))
// 		usleep(50);
// }

int	grab_forks(t_philo *philo)
{
	philo->r_fork = philo->id;
	philo->l_fork = (philo->id + 1) % philo->table->num_philo;
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	else
		pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	logger(philo, "has taken a fork");
	if (philo->table->num_philo == 1)
		return (1);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	else
		pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	logger(philo, "has taken a fork");
	return (0);
}

void	eat(t_philo *philo)
{
	logger(philo, "is eating");
	pthread_mutex_lock(&philo->table->eating);
	philo->last_meal = get_time() - philo->table->time_start;
	pthread_mutex_unlock(&philo->table->eating);
	usleep(philo->table->tt_eat);
	pthread_mutex_lock(&philo->table->eating);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->table->eating);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	// if (philo->id % 2 != 0)
	// {
	// 	logger(philo, "is sleeping");
	// 	usleep(philo->table->tt_sleep);
	// }
	while (1)
	{
		if (grab_forks(philo))
			break ;
		eat(philo);
		pthread_mutex_lock(&philo->table->exit);
		if (philo->table->dead_philo || philo->table->all_satisfied)
		{
			pthread_mutex_unlock(&philo->table->exit);
			pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
			pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
			break;
		}
		pthread_mutex_unlock(&philo->table->exit);
		pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
		logger(philo, "is sleeping");
		usleep(philo->table->tt_sleep);
		logger(philo, "is thinking");
	}
	return (NULL);
}
