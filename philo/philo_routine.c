/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:42:00 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/02 00:15:09 by mprokope         ###   ########.fr       */
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
	better_sleep(philo->data->info->time_to_die, philo);
	return (NULL);
}

//even
void	right_forkers(t_philo *philo)
{
	print_state(philo, "is thinking");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	if (dead_check(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_ms();
	if (philo->data->info->to_be_full > -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_meal_lock);
	is_fool(philo);
	better_sleep(philo->data->info->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_state(philo, "is sleeping");
	better_sleep(philo->data->info->time_to_sleep, philo);
}

//odd
void	left_forkers(t_philo *philo)
{
	print_state(philo, "is thinking");
	if (philo->num_p % 4 == 1)
		better_sleep(1, philo);
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	if (dead_check(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_ms();
	if (philo->data->info->to_be_full > -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_meal_lock);
	is_fool(philo);
	better_sleep(philo->data->info->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_state(philo, "is sleeping");
	better_sleep(philo->data->info->time_to_sleep, philo);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	is_start(philo);
	if (philo->data->info->number_of_philos == 1)
		return (solo_solo(philo));
	if (philo->num_p % 2 == 0)
		better_sleep(philo->data->info->time_to_eat / 2, philo);
	while (!dead_check(philo->data))
	{
		if (philo->num_p % 2)
			left_forkers(philo);
		else
			right_forkers(philo);
	}
	return (NULL);
}
