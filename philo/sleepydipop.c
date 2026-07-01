/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleepydipop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:45:30 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/02 00:51:15 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_start(t_philo *philo)
{
	while (42)
	{
		pthread_mutex_lock(&philo->data->starty);
		if (philo->data->start)
		{
			pthread_mutex_unlock(&philo->data->starty);
			break ;
		}
		pthread_mutex_unlock(&philo->data->starty);
		usleep(100);
	}
}

void	is_fool(t_philo *philo)
{
	if (philo->meals_eaten == philo->data->info->to_be_full)
	{
		pthread_mutex_lock(&philo->data->fool);
		philo->data->full++;
		pthread_mutex_unlock(&philo->data->fool);
	}
}

long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	better_sleep(long to_sleep, t_philo *philo)
{
	long	start;

	start = get_ms();
	while (!dead_check(philo->data))
	{
		if (get_ms() - start >= to_sleep)
			return ;
		usleep(200);
	}
}
