/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:35:42 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 22:45:59 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_error(char *s)
{
	if (s == NULL)
		return ;
	while (*s)
		write(2, s++, 1);
}

void	print_action(t_dinner *philo, char *message, long long timestamp)
{
	sem_wait(philo->print);
	printf("%lld %d %s\n", timestamp, philo->philo_id, message);
	sem_post(philo->print);
}

void	end_simulation(t_dinner *philo)
{
	int		i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		waitpid(-1, &philo->exit_status, 0);
		if (WIFEXITED(philo->exit_status)
			&& WEXITSTATUS(philo->exit_status) == HUNGER)
		{
			i = 0;
			while (i < philo->num_of_philos)
			{
				kill(philo->philo_pid[i], SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
	sem_close(philo->print);
	sem_close(philo->forks);
	free(philo->philo_pid);
	free(philo);
}

static int	check(unsigned long long n, long s, int dn)
{
	if (dn >= 20 || n > LONG_MAX)
		return (-1);
	return (n * s);
}

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
