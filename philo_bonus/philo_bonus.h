/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:35:28 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 20:35:28 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

# define MS 1000
# define HUNGER 66
# define FULL 99

# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_dinner
{
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*meal_time;
	char			*meal_time_name;
	int				*philo_pid;
	int				num_of_philos;
	int				philo_id;
	long long		last_meal;
	pthread_t		doctor;
	int				exit_status;
	int				enough_meals;
	int				ready_flag;
	int				num_of_active_philos;
	int				num_times_to_eat;
}					t_dinner;

t_dinner	*init_dinner(int ac, char **av);
long		get_number(const char *str);
int			parse_it(int ac, char **av);
void		print_error(char *s);
void		usleep_plus(long long time_to_sleep_in_MCS);
long long	get_actual_time(void);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(int n);
void		*doctor(void *args);
void		philo_routine(t_dinner *philo);
void		end_simulation(t_dinner *philo);
void		print_action(t_dinner *philo, char *message, long long timestamp);

#endif
