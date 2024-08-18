/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:24:52 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 16:09:13 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_fork *fork, int number_of_philos, t_dinner *dinner)
{
	int	index;

	index = 0;
	while (index < number_of_philos)
	{
		fork[index].id = index;
		if (pthread_mutex_init(&fork[index].fork, NULL))
		{
			while (index >= 0)
			{
				pthread_mutex_destroy(&fork[index].fork);
				index--;
			}
			urgent_free(dinner);
			pthread_mutex_destroy(&dinner->increment);
			pthread_mutex_destroy(&dinner->meals);
			return (-1);
		}
		index++;
	}
	return (0);
}

void	destroy_forks(t_dinner *dinner)
{
	int		index;
	t_fork	*forks;

	index = 0;
	forks = dinner->all_forks;
	while (index < dinner->num_of_philos)
	{
		pthread_mutex_destroy(&forks[index].fork);
		index++;
	}
}

void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->dinner->num_of_philos;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}
