/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:10:36 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/30 18:46:46 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (!dead_check(philo->data))
		printf("%ld %ld %s \n", get_ms() - philo->data->info->start_time,
			philo->num_p, state);
	pthread_mutex_unlock(&philo->data->print_lock);
}
