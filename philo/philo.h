/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:55:56 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 20:22:27 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_dinner	t_dinner;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

# define MS 1e3

# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_dinner
{
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_times_to_eat;
	long long		start_time;
	int				num_of_philos;
	int				end;
	int				enough_meals;
	int				ready_flag;
	int				num_of_active_philos;
	pthread_t		doctor;
	t_philo			*all_philos;
	t_fork			*all_forks;
	pthread_mutex_t	get_set;
	pthread_mutex_t	meals;
	pthread_mutex_t	increment;
	pthread_mutex_t	print;
}					t_dinner;

typedef struct s_philo
{
	long long		last_meal;
	pthread_t		thread;
	int				meals_eaten;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_dinner		*dinner;
	pthread_mutex_t	lock;
	int				id;
}					t_philo;

void		free_all(t_dinner *dinner);
void		print_error(char *s);
void		urgent_free(t_dinner *dinner);
void		destroy_forks(t_dinner *dinner);
int			check(unsigned long long n, long s, int dn);
void		error_1(t_dinner *dinner);
void		error_2(t_dinner *dinner);
int			create_x_philos(t_dinner *dinner);
int			join_philos(t_dinner *dinner);
void		the_end(t_dinner *dinner);
void		destroy_ph_locks(t_dinner *dinner);
void		detach_philos(t_dinner *dinner);
long		get_number(const char *str);
int			parse_it(int ac, char **av);
long		check_arg(int ac, char **av);
int			init_forks(t_fork *fork, int number_of_philos, t_dinner *dinner);
int			init_philos(t_philo *philo, int number_of_philos, t_dinner *dinner);
int			init_dinner(int ac, char **av, t_dinner *dinner);
void		assign_forks(t_philo *philo, t_fork *fork, int number_of_philos);
void		safe_setter_int(int value, int *to_set, pthread_mutex_t *lock);
int			safe_getter_int(int *to_get, pthread_mutex_t *lock);
void		safe_increment_int(int *to_increment, pthread_mutex_t *lock);
void		safe_setter_st(long long value, long long *to_set,
				pthread_mutex_t *lock);
long long	safe_getter_st(long long *to_get, pthread_mutex_t *lock);
long long	get_actual_time(void);
void		usleep_plus(long long time_to_sleep_in_MCS, t_dinner *dinner);
void		print_action(char *action, t_philo *philo, t_dinner *dinner);
void		*philo_routine(void *args);
void		*doctor_routine(void *args);
void		init_philos_1(t_dinner *dinner, t_philo *philo, int index);
int			init_dinner_2(t_dinner *dinner);
int			init_dinner_3(t_dinner *dinner);
void		init_flags(t_dinner *dinner);

#endif
