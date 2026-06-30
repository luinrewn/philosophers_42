/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 18:34:26 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/30 17:50:49 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_philo *philo, long num_p)
{
	long	i;

	i = 0;
	free(philo->data->info);
	while (i < num_p)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		pthread_mutex_destroy(&philo[i].last_meal_lock);
		i++;
	}
	pthread_mutex_destroy(&philo->data->print_lock);
	pthread_mutex_destroy(&philo->data->death_lock);
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}
