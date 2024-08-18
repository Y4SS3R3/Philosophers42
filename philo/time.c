/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:45:55 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 20:05:53 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_plus(long long time_to_sleep_in_MS, t_dinner *dinner)
{
	long long	t;

	t = get_actual_time();
	while (!safe_getter_int(&dinner->end, &dinner->get_set))
	{
		if (get_actual_time() - t >= time_to_sleep_in_MS)
			break ;
		usleep(500);
	}
}

long long	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * MS + time.tv_usec / MS);
}
