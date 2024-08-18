/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:23:08 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 15:52:48 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos_1(t_dinner *dinner, t_philo *philo, int index)
{
	philo[index].id = index + 1;
	philo[index].dinner = dinner;
	philo[index].meals_eaten = 0;
}

int	init_dinner_2(t_dinner *dinner)
{
	if (dinner->all_forks == NULL)
	{
		free(dinner->all_philos);
		print_error("Problem while allocating for fork\n");
		return (-1);
	}
	if (pthread_mutex_init(&dinner->get_set, NULL))
	{
		free_all(dinner);
		print_error("Initializing mutex failed[001]\n");
		return (-1);
	}
	return (0);
}

int	init_dinner_3(t_dinner *dinner)
{
	if (pthread_mutex_init(&dinner->increment, NULL))
	{
		free_all(dinner);
		pthread_mutex_destroy(&dinner->get_set);
		print_error("Initializing mutex failed[011]\n");
		return (-1);
	}
	if (pthread_mutex_init(&dinner->print, NULL))
	{
		free_all(dinner);
		pthread_mutex_destroy(&dinner->get_set);
		pthread_mutex_destroy(&dinner->increment);
		print_error("Initializing mutex failed[002]\n");
		return (-1);
	}
	return (0);
}

void	init_flags(t_dinner *dinner)
{
	dinner->num_of_active_philos = 0;
	dinner->end = 0;
	dinner->enough_meals = 0;
	dinner->ready_flag = 0;
}
