/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:53:26 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/15 21:04:04 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//---------------------------------INCLUDES-------------------------------------
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

//---------------------------------STRUCTS--------------------------------------
typedef struct s_philo
{
	int				id;
	int				n_meals;
	int				r_fork;
	int				l_fork;
	long long		last_meal;
	struct s_table	*table;

}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating;
	pthread_mutex_t	exit;
	pthread_t		supervisor;
	pthread_t		*threads;
	t_philo			*philos;
	int				dead_philo;
	int				all_satisfied;
	int				num_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				meal_cap;
	long long		start_time;
}	t_table;

//---------------------------------FUNCTIONS------------------------------------
// check.c
void		*supervise(void *var);
int			check_starved(t_philo *philos);
int			check_satisfied(t_philo *philo);
int			check_exit(t_philo *philo);
void		verify_arguments(char **argv);

// init.c
t_table		*table_init(int argc, char **argv);
void		mutex_init(t_table *table);
int			create_threads(t_table *table);

// routine.c
void		logger(t_philo *philo, char *str);
void		*routine(void *philo);

// utils.c
int			ft_atoi(const char *str);
long long	get_time(void);
long long	elapsed_time(t_philo *philo);

#endif
