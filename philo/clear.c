/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:23:11 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 19:58:48 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	detach_philos(t_dinner *dinner)
{
	t_philo	*philos;
	int		i;

	philos = dinner->all_philos;
	i = 0;
	while (i < dinner->num_of_philos)
	{
		if (pthread_detach(philos[i].thread))
			print_error("ERROR\n");
		i++;
	}
}

void	urgent_free(t_dinner *dinner)
{
	free_all(dinner);
	pthread_mutex_destroy(&dinner->print);
	pthread_mutex_destroy(&dinner->get_set);
}

void	free_all(t_dinner *dinner)
{
	free(dinner->all_forks);
	free(dinner->all_philos);
}

void	the_end(t_dinner *dinner)
{
	pthread_detach(dinner->doctor);
	destroy_forks(dinner);
	destroy_ph_locks(dinner);
	free_all(dinner);
	pthread_mutex_destroy(&dinner->meals);
	pthread_mutex_destroy(&dinner->increment);
}
