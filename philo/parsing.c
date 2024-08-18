/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:46:23 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 20:17:13 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_it(int ac, char **av)
{
	char			*msg;
	int				res;
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		print_error("\"gettimeofday()\" is not available\n");
		return (-1);
	}
	res = check_arg(ac, av);
	if (res != 0)
	{
		if (res == 1)
			msg = "❌Arguments should contain numbers ONLY!\n";
		if (res == 2)
			msg = "❌wrong value of argument!\n";
		if (res == -1)
			msg = "❌Wrong number of args!\n";
		printf("%s", msg);
		return (-1);
	}
	else
		return (0);
}
