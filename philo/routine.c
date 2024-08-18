/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:32:58 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 20:07:43 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking_routine(t_philo *philo)
{
	long long	time_to_think;
	t_dinner	*dinner;

	dinner = philo->dinner;
	if (philo->dinner->num_of_philos % 2 == 0)
		return ;
	time_to_think = philo->dinner->time_to_eat * 2
		- philo->dinner->time_to_sleep;
	if (time_to_think <= 0)
		return ;
	print_action(THINKING, philo, dinner);
	usleep_plus(time_to_think / 4, dinner);
}

static void	*one_philo_special(t_philo *philo, t_dinner *dinner)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_action(TAKE_FORK, philo, dinner);
	pthread_mutex_unlock(&philo->first_fork->fork);
	usleep_plus(dinner->time_to_die, dinner);
	print_action(DIED, philo, dinner);
	safe_setter_int(1, &dinner->end, &dinner->get_set);
	return (NULL);
}

static void	eating_routine(t_philo *philo, t_dinner *dinner)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_action(TAKE_FORK, philo, dinner);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_action(TAKE_FORK, philo, dinner);
	safe_setter_st(get_actual_time(), &philo->last_meal, &philo->lock);
	print_action(EATING, philo, dinner);
	usleep_plus(dinner->time_to_eat, dinner);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
	philo->meals_eaten++;
	if (philo->meals_eaten == dinner->num_times_to_eat)
		safe_increment_int(&dinner->enough_meals, &dinner->meals);
}

void	*philo_routine(void *args)
{
	t_dinner	*dinner;
	t_philo		*philo;

	philo = (t_philo *)args;
	dinner = philo->dinner;
	while (!safe_getter_int(&dinner->ready_flag, &dinner->get_set)
		&& !safe_getter_int(&dinner->end, &dinner->get_set));
	safe_setter_st(get_actual_time(), &philo->last_meal, &philo->lock);
	safe_increment_int(&dinner->num_of_active_philos, &dinner->get_set);
	if (dinner->num_of_philos == 1)
		return (one_philo_special(philo, dinner));
	while (1)
	{
		if (safe_getter_int(&dinner->end, &dinner->get_set))
			break ;
		eating_routine(philo, dinner);
		print_action(SLEEPING, philo, dinner);
		usleep_plus(dinner->time_to_sleep, dinner);
		thinking_routine(philo);
	}
	return (NULL);
}
