/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:10:36 by mprokope          #+#    #+#             */
/*   Updated: 2026/05/09 18:57:16 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (!dead_check(philo->data))
		printf("%ld %ld %s \n", get_ms(), philo->num_p, state);
	pthread_mutex_unlock(&philo->data->print_lock);
}
