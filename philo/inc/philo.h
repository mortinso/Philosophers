/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:53:26 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/06 18:30:42 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//---------------------------------INCLUDES-------------------------------------
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

//---------------------------------STRUCTS--------------------------------------
typedef struct s_table {
	int	num_philo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	min_eat;
}	t_table;

//---------------------------------FUNCTIONS------------------------------------
// check.c
void	verify_arguments(char **argv);

// init.c
t_table	*table_init(int argc, char **argv);

// utils.c
int		ft_atoi(const char *str);

#endif