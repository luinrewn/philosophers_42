/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:47:21 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/30 21:19:26 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h> //TODO figure out
# include <pthread.h> //TODO figure out

# define FIRST_USE "Usage: <num_of_philos> <time_to_die> "
# define SECOND_USE "<time_to_eat> <time_to_sleep> | <num_to_be_full>\n"

typedef struct s_info
{
	long	number_of_philos;
	time_t	time_to_die;
	time_t	start_time;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	long	to_be_full;
}				t_info;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	long			full;
	pthread_mutex_t	fool;
	int				dead;
	t_info			*info;
}				t_data;

typedef struct s_philo
{
	long			num_p;
	long			last_meal;
	long			meals_eaten;
	long			first_time;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}				t_philo;

int		ft_strlen(char *line);
long	ft_atol(const char *nptr);
int		check_input(int argc, char **argv);
// 0 = error, 1 = success;
int		ft_is_number(char c);
t_philo	*init(long num_p, char **argv);
void	clean_up(t_philo *philo, long num_p);

//Time Fucntions
long	get_ms(void);
void	better_sleep(long to_sleep);

//Threads
int		create_threads(pthread_t **thr, long num, t_philo *philo);
void	join_threads(pthread_t	**thr, t_philo *philo);

//Printing
void	print_state(t_philo *philo, char *state);

void	*philo_routine(void *arg);
void	*monitoring(void *arg);
int		dead_check(t_data *data);
void	is_fool(t_philo *philo);

#endif
