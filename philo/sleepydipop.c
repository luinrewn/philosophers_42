/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleepydipop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:45:30 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/30 21:18:47 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	better_sleep(long to_sleep)
{
	long	start;
	long	rem;
	
	start = get_ms();
	while (1)
	{
		rem = to_sleep - (get_ms() - start);
		if (rem <= 0)
			return ;
		if (rem > 5)
			usleep(rem * 500);
		else
			usleep(100);
	}
}
