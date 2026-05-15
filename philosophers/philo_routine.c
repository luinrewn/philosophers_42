/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:42:00 by mprokope          #+#    #+#             */
/*   Updated: 2026/05/09 22:17:12 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}

void	*solo_solo(t_philo *philo)
{
	print_state(philo, "has taken the fork");
	usleep(philo->data->info->time_to_die);
	return (NULL);
}

//even
void	right_forkers(t_philo *philo)
{
	usleep(1000);
	print_state(philo, "is thinking");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_ms();
	if (philo->data->info->to_be_full > -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_meal_lock);
	better_sleep(philo->data->info->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_state(philo, "is sleeping");
	better_sleep(philo->data->info->time_to_sleep);
}

//odd
void	left_forkers(t_philo *philo)
{
	print_state(philo, "is thinking");
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_ms();
	if (philo->data->info->to_be_full > -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_meal_lock);
	better_sleep(philo->data->info->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_state(philo, "is sleeping");
	better_sleep(philo->data->info->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->data->info->number_of_philos == 1)
		return (solo_solo(philo));
	while (!dead_check(philo->data) && !(philo->num_p % 2))
		right_forkers(philo);
	while (!dead_check(philo->data))
		left_forkers(philo);
	return (NULL);
}
