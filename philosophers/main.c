/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:59:23 by mprokope          #+#    #+#             */
/*   Updated: 2026/05/09 18:45:34 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	*thr;

	if (!check_input(argc, argv))
		return (write(2, FULL_USE, (sizeof(FULL_USE) - 1)), 1);
	philo = init(ft_atol(argv[1]), argv);
	if (!philo)
		return (1);
	thr = NULL;
	//TODO Created threads with routine; Left to do the overmentioned routine;
	if (create_threads(&thr, philo->data->info->number_of_philos, philo))
		return (clean_up(philo, ft_atol(argv[1])), free(thr), 1);
	//TODO Join threads;
	join_threads(&thr, philo);
	clean_up(philo, ft_atol(argv[1]));
	free(thr);
	return (0);
}
