/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:59:23 by mprokope          #+#    #+#             */
/*   Updated: 2026/05/19 21:12:26 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	join_threads(&thr, philo);
	clean_up(philo, ft_atol(argv[1]));
	free(thr);
	return (0);
}
