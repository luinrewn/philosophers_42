/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:59:23 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/01 23:35:01 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_time(t_philo *philo)
{
	time_t	start;
	long	i;

	start = get_ms();
	i = 0;
	while (i < philo->data->info->number_of_philos)
	{
		philo[i++].last_meal = start;
	}
}


void	sleep_think(t_philo *philo)
{
	long	think;

	think = philo->data->info->time_to_eat - philo->data->info->time_to_sleep;
	if (think > 0)
		better_sleep(think / 2, philo);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	*thr;

	if (!check_input(argc, argv))
	{
		write(2, FIRST_USE, (sizeof(FIRST_USE) - 1));
		write(2, SECOND_USE, (sizeof(SECOND_USE) - 1));
		return (1);
	}
	philo = init(ft_atol(argv[1]), argv);
	if (!philo)
		return (1);
	thr = NULL;
	if (create_threads(&thr, philo->data->info->number_of_philos, philo))
		return (clean_up(philo, ft_atol(argv[1])), free(thr), 1);
	pthread_mutex_lock(&philo->data->starty);
	philo->data->start = 1;
	setup_time(philo);
	pthread_mutex_unlock(&philo->data->starty);
	join_threads(&thr, philo);
	clean_up(philo, ft_atol(argv[1]));
	free(thr);
	return (0);
}
