/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:57:10 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 20:07:15 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_sim(t_dinner *dinner)
{
	if (init_forks(dinner->all_forks, dinner->num_of_philos, dinner))
	{
		print_error("Initializing forks failed\n");
		return (1);
	}
	if (init_philos(dinner->all_philos, dinner->num_of_philos, dinner))
	{
		print_error("Initializing philos failed\n");
		return (1);
	}
	return (0);
}

static int	no_eat(t_dinner *dinner)
{
	free_all(dinner);
	pthread_mutex_destroy(&dinner->print);
	pthread_mutex_destroy(&dinner->get_set);
	pthread_mutex_destroy(&dinner->increment);
	pthread_mutex_destroy(&dinner->meals);
	return (0);
}

int	main(int ac, char **av)
{
	t_dinner	dinner;

	if (init_dinner(ac, av, &dinner))
		return (1);
	if (!dinner.num_times_to_eat || !dinner.num_of_philos)
		return (no_eat(&dinner));
	if (init_sim(&dinner))
		return (1);
	if (create_x_philos(&dinner))
		return (1);
	if (pthread_create(&dinner.doctor, NULL, doctor_routine, &dinner))
	{
		error_1(&dinner);
		return (1);
	}
	safe_setter_st(get_actual_time(), &dinner.start_time, &dinner.get_set);
	safe_setter_int(1, &dinner.ready_flag, &dinner.get_set);
	if (join_philos(&dinner))
		return (1);
	the_end(&dinner);
}
