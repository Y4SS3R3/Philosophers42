/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:10:36 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 22:26:07 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	error_2(t_dinner *dinner)
{
	free(dinner->philo_pid);
	sem_close(dinner->print);
	sem_close(dinner->forks);
	free(dinner);
	print_error("Cannot set name for semaphore\n");
	exit(EXIT_FAILURE);
}

static void	inherit_data(t_dinner *dinner, int i)
{
	char	*sem_name;
	char	*tmp;

	dinner->philo_id = i + 1;
	dinner->last_meal = get_actual_time();
	tmp = ft_itoa(i);
	if (tmp == NULL)
		error_2(dinner);
	sem_name = ft_strjoin("/mt", tmp);
	free(tmp);
	if (sem_name == NULL)
		error_2(dinner);
	dinner->meal_time_name = sem_name;
	sem_unlink(sem_name);
	dinner->meal_time = sem_open(sem_name, O_CREAT, 0644, 1);
	if (dinner->meal_time == SEM_FAILED)
	{
		free(dinner->philo_pid);
		free(dinner->meal_time_name);
		free(dinner);
		sem_close(dinner->print);
		sem_close(dinner->forks);
		print_error("Sem_open() failed!\n");
		exit(EXIT_FAILURE);
	}
}

static void	create_x_philos(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->num_of_philos)
	{
		dinner->philo_pid[i] = fork();
		if (dinner->philo_pid[i] == -1)
		{
			free(dinner->philo_pid);
			sem_close(dinner->print);
			sem_close(dinner->forks);
			free(dinner);
			print_error("Fork() failed\n");
			exit(EXIT_FAILURE);
		}
		if (dinner->philo_pid[i] == 0)
		{
			inherit_data(dinner, i);
			philo_routine(dinner);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	if (parse_it(ac, av))
		return (13);
	dinner = init_dinner(ac, av);
	sem_unlink("/print");
	sem_unlink("/forks");
	if (!dinner)
		return (37);
	if (dinner->num_times_to_eat == 0 || dinner->num_of_philos == 0)
	{
		free(dinner->philo_pid);
		sem_close(dinner->print);
		sem_close(dinner->forks);
		free(dinner);
		return (0);
	}
	dinner->start_time = get_actual_time();
	create_x_philos(dinner);
	end_simulation(dinner);
}
