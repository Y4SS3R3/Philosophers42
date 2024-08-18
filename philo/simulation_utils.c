/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:26:09 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 23:37:45 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_philos(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->num_of_philos)
	{
		if (pthread_join(dinner->all_philos[i++].thread, NULL))
		{
			error_2(dinner);
			return (-1);
		}
	}
	return (0);
}

void	destroy_ph_locks(t_dinner *dinner)
{
	int		index;
	t_philo	*philos;

	index = 0;
	philos = dinner->all_philos;
	while (index < dinner->num_of_philos)
	{
		pthread_mutex_destroy(&philos[index].lock);
		index++;
	}
}

int	create_x_philos(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->num_of_philos)
	{
		if (pthread_create(&dinner->all_philos[i].thread, NULL
				, philo_routine, &dinner->all_philos[i]))
		{
			safe_setter_int(1, &dinner->end, &dinner->get_set);
			destroy_forks(dinner);
			destroy_ph_locks(dinner);
			urgent_free(dinner);
			pthread_mutex_destroy(&dinner->meals);
			pthread_mutex_destroy(&dinner->increment);
			print_error("Error while creating threads.\n");
			return (-1);
		}
		i++;
	}
	return (0);
}
