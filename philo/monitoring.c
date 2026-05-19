/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:20:40 by mprokope          #+#    #+#             */
/*   Updated: 2026/05/19 21:08:46 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exterminate(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->death_lock);
}

int	check_if_starved(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_lock);
	if (get_ms() - philo->last_meal > philo->data->info->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_lock);
		print_state(philo, "died");
		exterminate(philo->data);
		return (0);
	}
	pthread_mutex_unlock(&philo->last_meal_lock);
	return (1);
}

int	fullnes_check(t_philo *philo)
{
	long	i;

	i = 0;
	while (i < philo->data->info->number_of_philos)
	{
		pthread_mutex_lock(&philo->last_meal_lock);
		if (philo[i].meals_eaten < philo->data->info->to_be_full)
		{
			pthread_mutex_unlock(&philo->last_meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->last_meal_lock);
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;
	long	i;

	philo = (t_philo *)arg;
	while (42)
	{
		i = 0;
		while (i < philo->data->info->number_of_philos)
		{
			if (!check_if_starved(&philo[i]))
				return (NULL);
			if (philo->data->info->to_be_full > -1 && philo[i].meals_eaten
				>= philo->data->info->to_be_full)
				if (!fullnes_check(philo))
					return (exterminate(philo->data), NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
