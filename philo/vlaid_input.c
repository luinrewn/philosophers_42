/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlaid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:51:20 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/30 17:56:36 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_number(char c)
{
	return (((unsigned int)(c - 48)) < 10);
}

static int	ft_string_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_is_number(str[i++]))
			return (0);
	return (1);
}

int	check_input(int argc, char **argv)
{
	long	i;

	if (argc == 5 || argc == 6)
	{
		i = 0;
		while (argv[++i])
		{
			if (ft_strlen(argv[i]) > 10)
				return (0);
			if (!ft_string_numeric(argv[i]))
				return (0);
			if (ft_atol(argv[i]) > 2147483647 || ft_atol(argv[i]) <= 0)
				return (0);
		}
		return (1);
	}
	return (0);
}
