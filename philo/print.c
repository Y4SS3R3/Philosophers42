/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:27:28 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 19:59:46 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(char *action, t_philo *philo, t_dinner *dinner)
{
	pthread_mutex_lock(&dinner->print);
	if (safe_getter_int(&dinner->end, &dinner->get_set))
	{
		pthread_mutex_unlock(&dinner->print);
		return ;
	}
	printf("%lld %d %s\n", get_actual_time()
		- dinner->start_time, philo->id, action);
	pthread_mutex_unlock(&dinner->print);
}

void	error_1(t_dinner *dinner)
{
	safe_setter_int(1, &dinner->end, &dinner->get_set);
	detach_philos(dinner);
	destroy_forks(dinner);
	destroy_ph_locks(dinner);
	urgent_free(dinner);
	pthread_mutex_destroy(&dinner->meals);
	pthread_mutex_destroy(&dinner->increment);
	print_error("Creating doctor thread failed\n");
}

void	error_2(t_dinner *dinner)
{
	pthread_detach(dinner->doctor);
	safe_setter_int(1, &dinner->end, &dinner->get_set);
	destroy_forks(dinner);
	destroy_ph_locks(dinner);
	urgent_free(dinner);
	pthread_mutex_destroy(&dinner->meals);
	pthread_mutex_destroy(&dinner->increment);
	print_error("Joining threads failed\n");
}
