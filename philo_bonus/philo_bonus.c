/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:04:51 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 22:30:46 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_routine(t_dinner *philo)
{
	if (pthread_create(&philo->doctor, NULL, &doctor, philo))
		print_error("Pthread_create() failed!\n");
	if (philo->philo_id % 2)
		usleep(800);
	while (1)
	{
		sem_wait(philo->forks);
		print_action(philo, TAKE_FORK, get_actual_time() - philo->start_time);
		sem_wait(philo->forks);
		print_action(philo, TAKE_FORK, get_actual_time() - philo->start_time);
		sem_wait(philo->meal_time);
		philo->last_meal = get_actual_time();
		sem_post(philo->meal_time);
		print_action(philo, EATING, get_actual_time() - philo->start_time);
		usleep_plus(philo->time_to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo->enough_meals++;
		print_action(philo, SLEEPING, get_actual_time() - philo->start_time);
		usleep_plus(philo->time_to_sleep);
		print_action(philo, THINKING, get_actual_time() - philo->start_time);
	}
}
