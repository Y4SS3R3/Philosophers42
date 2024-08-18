/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:55:39 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 17:14:19 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo *philo, int number_of_philos, t_dinner *dinner)
{
	int		index;
	t_fork	*forks;

	index = -1;
	forks = dinner->all_forks;
	philo->last_meal = 0;
	while (++index < number_of_philos)
	{
		init_philos_1(dinner, philo, index);
		assign_forks(&philo[index], forks, index);
		if (pthread_mutex_init(&philo[index].lock, NULL))
		{
			while (index >= 0)
			{
				pthread_mutex_destroy(&philo[index].lock);
				index--;
			}
			destroy_forks(dinner);
			urgent_free(dinner);
			pthread_mutex_destroy(&dinner->increment);
			pthread_mutex_destroy(&dinner->meals);
			return (-1);
		}
	}
	return (0);
}

static int	init_dinner_1(t_dinner *dinner)
{
	dinner->all_forks = malloc(sizeof(t_fork) * dinner->num_of_philos);
	if (init_dinner_2(dinner))
		return (-1);
	if (init_dinner_3(dinner))
		return (-1);
	if (pthread_mutex_init(&dinner->meals, NULL))
	{
		free_all(dinner);
		pthread_mutex_destroy(&dinner->get_set);
		pthread_mutex_destroy(&dinner->increment);
		pthread_mutex_destroy(&dinner->print);
		print_error("Initializing mutex failed[022]\n");
		return (-1);
	}
	return (0);
}

int	init_dinner(int ac, char **av, t_dinner *dinner)
{
	if (parse_it(ac, av))
		return (-1);
	dinner->num_of_philos = get_number(av[1]);
	if (dinner->num_of_philos > 1000)
	{
		printf("❌Number of philos might cause potential errors!\n");
		return (-1);
	}
	dinner->time_to_die = get_number(av[2]);
	dinner->time_to_eat = get_number(av[3]);
	dinner->time_to_sleep = get_number(av[4]);
	if (ac == 6)
		dinner->num_times_to_eat = get_number(av[5]);
	else
		dinner->num_times_to_eat = -1;
	dinner->all_philos = malloc(sizeof(t_philo) * dinner->num_of_philos);
	if (dinner->all_philos == NULL)
	{
		print_error("Problem while allocating for philos\n");
		return (-1);
	}
	if (init_dinner_1(dinner))
		return (-1);
	init_flags(dinner);
	return (0);
}
