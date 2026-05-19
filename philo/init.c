/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:44:07 by mprokope          #+#    #+#             */
/*   Updated: 2026/05/19 21:07:53 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*populate_info(char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->number_of_philos = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		info->to_be_full = ft_atol(argv[5]);
	else
		info->to_be_full = -1;
	return (info);
}

t_data	*init_data(long num_p)
{
	t_data	*data;
	long	i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * num_p);
	if (!data->forks)
		return (free(data), NULL);
	data->dead = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	i = 0;
	while (i < num_p)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (data);
}

t_philo	*create_philo(long num_p, t_info *info, t_data *data)
{
	t_philo	*philo;
	long	i;

	philo = malloc(sizeof(t_philo) * num_p);
	if (!philo)
		return (NULL);
	i = 0;
	data->info = info;
	while (i < num_p)
	{
		philo[i].num_p = i + 1;
		philo[i].data = data;
		philo[i].last_meal = get_ms();
		philo[i].meals_eaten = 0;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % num_p];
		pthread_mutex_init(&philo[i].last_meal_lock, NULL);
		i++;
	}
	return (philo);
}

t_philo	*init(long num_p, char **argv)
{
	t_info	*info;
	t_data	*data;
	t_philo	*philo;

	info = populate_info(argv);
	if (!info)
		return (NULL);
	data = init_data(num_p);
	if (!data)
		return (free(info), NULL);
	philo = create_philo(num_p, info, data);
	if (!philo)
	{
		free(info);
		while (num_p--)
			pthread_mutex_destroy(&data->forks[num_p]);
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->death_lock);
		free(data->forks);
		free(data);
	}
	return (philo);
}
