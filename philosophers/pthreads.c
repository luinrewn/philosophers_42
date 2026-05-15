/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 19:18:17 by mprokope          #+#    #+#             */
/*   Updated: 2026/05/09 18:54:11 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_threads(pthread_t **thr, long num)
{
	(*thr) = malloc(sizeof(pthread_t) * (num + 1));
	if (!(*thr))
		return (1);
	return (0);
}

int	clean_pthreads_fail(pthread_t **thr, long i)
{
	if (!i)
		return (1);
	while (i)
		pthread_join((*thr)[i--], NULL);
	pthread_join((*thr)[i], NULL);
	return (1);
}
//cloude sugested to switch thr to a ** pointer.
int	create_threads(pthread_t **thr, long num, t_philo *philo)
{
	long	i;

	if (alloc_threads(thr, num))
		return (1);
	i = 0;
	if (pthread_create(&(*thr)[i], NULL, monitoring, philo))
		return (1);
	i = 1;
	while (i <= num)
	{
		if (pthread_create(&(*thr)[i], NULL, philo_routine, &philo[i - 1]))
			return (clean_pthreads_fail(thr, i));
		i++;
	}
	return (0);
}

void	join_threads(pthread_t	**thr, t_philo *philo)
{
	long	i;

	i = 0;
	while (i < philo->data->info->number_of_philos + 1)
		pthread_join((*thr)[i++], NULL);
}
