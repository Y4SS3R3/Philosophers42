/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:15:05 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 20:06:45 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_number(const char *str)
{
	long long			i;
	unsigned long long	n;
	long				s;
	int					digitn;

	i = 0;
	n = 0;
	s = 1;
	digitn = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		digitn++;
		n = n * 10 + (str[i++] - 48);
	}
	return (check(n, s, digitn));
}
