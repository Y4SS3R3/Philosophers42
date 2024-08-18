/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:06:36 by ymassiou          #+#    #+#             */
/*   Updated: 2024/07/27 15:42:59 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *s)
{
	if (s == NULL)
		return ;
	while (*s)
		write(2, s++, 1);
}

int	nbr_len(char *str)
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
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

long	check_arg(int ac, char **av)
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

int	check(unsigned long long n, long s, int dn)
{
	if (dn >= 20 && s > 0)
		return (-1);
	if (dn >= 20 && s < 0)
		return (0);
	if (n > LONG_MAX && s > 0)
		return (-1);
	if (n > LONG_MAX && s < 0)
		return (0);
	return (n * s);
}
