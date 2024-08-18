/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:35:05 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 22:22:38 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	error_1(t_dinner *res)
{
	free(res->philo_pid);
	sem_close(res->print);
	sem_unlink("/print");
	free(res);
	print_error("Sem_open() failed!\n");
	exit(EXIT_FAILURE);
}

static t_dinner	*init_part1(int ac, char **av)
{
	t_dinner	*res;

	res = malloc(sizeof(t_dinner));
	if (res == NULL)
	{
		print_error("Malloc() failed!\n");
		exit(EXIT_FAILURE);
	}
	res->num_of_philos = get_number(av[1]);
	res->time_to_die = get_number(av[2]);
	res->time_to_eat = get_number(av[3]);
	res->time_to_sleep = get_number(av[4]);
	if (res->num_of_philos > 1000)
	{
		printf("❌Number of philos might cause potential errors!\n");
		free(res);
		exit(EXIT_FAILURE);
	}
	if (ac == 6)
		res->num_times_to_eat = get_number(av[5]);
	else
		res->num_times_to_eat = -1;
	return (res);
}

t_dinner	*init_dinner(int ac, char **av)
{
	t_dinner	*res;

	res = init_part1(ac, av);
	res->exit_status = 0;
	res->philo_pid = malloc(sizeof(int) * res->num_of_philos);
	if (!res->philo_pid)
	{
		free(res);
		print_error("Malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	sem_unlink("/print");
	sem_unlink("/forks");
	res->print = sem_open("/print", O_CREAT, 0644, 1);
	if (res->print == SEM_FAILED)
	{
		free(res->philo_pid);
		free(res);
		print_error("Sem_open() failed!\n");
		exit(EXIT_FAILURE);
	}
	res->forks = sem_open("/forks", O_CREAT, 0644, res->num_of_philos);
	if (res->forks == SEM_FAILED)
		error_1(res);
	return (res);
}
