/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:50:21 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 20:06:17 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_setter_st(long long value,
			long long *to_set, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*to_set = value;
	pthread_mutex_unlock(lock);
}

void	safe_setter_int(int value, int *to_set, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*to_set = value;
	pthread_mutex_unlock(lock);
}

int	safe_getter_int(int *to_get, pthread_mutex_t *lock)
{
	int	res;

	pthread_mutex_lock(lock);
	res = *to_get;
	pthread_mutex_unlock(lock);
	return (res);
}

long long	safe_getter_st(long long *to_get, pthread_mutex_t *lock)
{
	long long	res;

	pthread_mutex_lock(lock);
	res = *to_get;
	pthread_mutex_unlock(lock);
	return (res);
}

void	safe_increment_int(int *to_increment, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	(*to_increment)++;
	pthread_mutex_unlock(lock);
}
