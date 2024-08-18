/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:39:54 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 15:25:27 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	died_from_hunger(t_philo *philo, t_dinner *dinner)
{
	safe_setter_int(1, &dinner->end, &dinner->get_set);
	pthread_mutex_lock(&dinner->print);
	printf("%lld %d %s\n", get_actual_time() - dinner->start_time,
		philo->id, DIED);
	pthread_mutex_unlock(&dinner->print);
}

static int	philo_is_full(t_dinner *dinner)
{
	if (dinner->num_times_to_eat != -1
		&& safe_getter_int(&dinner->enough_meals, &dinner->meals)
		>= dinner->num_of_philos)
	{
		safe_setter_int(1, &dinner->end, &dinner->get_set);
		return (1);
	}
	return (0);
}

static int	philo_must_die(t_philo *philo, t_dinner *dinner)
{
	long long	time;

	time = get_actual_time()
		- safe_getter_st(&philo->last_meal, &philo->lock);
	if (time >= dinner->time_to_die)
		return (1);
	return (0);
}

static void	checking_routine(t_dinner *dinner, int number_of_philos)
{
	t_philo	*philo;
	int		i;

	philo = dinner->all_philos;
	while (!safe_getter_int(&dinner->end, &dinner->get_set))
	{
		if (philo_is_full(dinner))
			break ;
		i = -1;
		while (++i < number_of_philos)
		{
			if (philo_is_full(dinner))
				return ;
			if (philo_must_die(&philo[i], dinner))
			{
				died_from_hunger(&philo[i], dinner);
				break ;
			}
		}
	}
}

void	*doctor_routine(void *args)
{
	t_dinner	*dinner;
	int			number_of_philos;

	dinner = (t_dinner *)args;
	number_of_philos = dinner->num_of_philos;
	while (safe_getter_int(&dinner->num_of_active_philos, &dinner->get_set)
		!= number_of_philos)
				;
	if (dinner->num_of_philos == 1)
		return (NULL);
	checking_routine(dinner, number_of_philos);
	return (NULL);
}
