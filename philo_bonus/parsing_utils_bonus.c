/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:35:14 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 22:51:44 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	nbr_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	only_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

static long	check_arg(int ac, char **av)
{
	int		i;
	long	num;

	i = 1;
	num = 0;
	if (ac != 5 && ac != 6)
		return (-1);
	while (i < ac)
	{
		if (!only_num(av[i]))
			return (1);
		num = get_number(av[i]);
		if (num > INT_MAX || nbr_len(av[i]) > 10 || num < 0)
			return (2);
		i++;
	}
	return (0);
}

int	parse_it(int ac, char **av)
{
	char			*msg;
	int				res;
	struct timeval	time;

	res = check_arg(ac, av);
	if (gettimeofday(&time, NULL) == -1)
	{
		print_error("\"gettimeofday()\" is not available\n");
		return (-1);
	}
	if (res != 0)
	{
		if (res == 1)
			msg = "❌Arguments should contain numbers ONLY!\n";
		if (res == 2)
			msg = "❌Wrong value of argument!\n";
		if (res == -1)
			msg = "❌Wrong number of args!\n";
		printf("%s", msg);
		return (-1);
	}
	else
		return (0);
}
