/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:34:58 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 22:19:59 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	calibrate_logic(t_dinner *philo)
{
	int	num;

	num = philo->num_of_philos;
	if (num % 2)
		return (get_actual_time() - philo->last_meal > philo->time_to_die);
	return (get_actual_time() - philo->last_meal >= philo->time_to_die);
}

static int	check_death(t_dinner *philo)
{
	if (calibrate_logic(philo))
	{
		sem_wait(philo->print);
		printf("%lld %d %s\n",
			get_actual_time() - philo->start_time, philo->philo_id, DIED);
		sem_post(philo->meal_time);
		return (1);
	}
	return (0);
}

static void	exit_if_cause(int cause)
{
	if (cause == HUNGER)
		exit (HUNGER);
	exit (FULL);
}

static void	end_it(t_dinner *philo, int cause)
{
	sem_close(philo->meal_time);
	sem_unlink(philo->meal_time_name);
	free(philo->meal_time_name);
	exit_if_cause(cause);
}

void	*doctor(void *args)
{
	t_dinner	*philo;
	int			cause;

	philo = (t_dinner *)args;
	cause = FULL;
	while (1)
	{
		usleep(100);
		sem_wait(philo->meal_time);
		if (check_death(philo))
		{
			cause = HUNGER;
			break ;
		}
		sem_post(philo->meal_time);
		if (philo->num_times_to_eat != -1
			&& philo->enough_meals >= philo->num_times_to_eat)
		{
			sem_post(philo->print);
			break ;
		}
	}
	end_it(philo, cause);
	return (NULL);
}
