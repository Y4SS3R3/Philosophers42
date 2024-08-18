/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:35:37 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 22:45:11 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	usleep_plus(long long time_to_sleep_in_MS)
{
	long long	t;

	t = get_actual_time();
	while (get_actual_time() - t < time_to_sleep_in_MS)
		usleep(500);
}

long long	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * MS + time.tv_usec / MS);
}
