/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:14:44 by mprokope          #+#    #+#             */
/*   Updated: 2026/04/23 18:12:46 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *nptr)
{
	int		i;
	long	result;
	int		minus;

	i = 0;
	result = 0;
	minus = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			minus = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + (nptr[i++] - '0');
	return (result * minus);
}
/*
#include <stdlib.h>
#include <stdio.h>
int	main(void)
{
	printf("     --123: %d\n", ft_atoi("--123"));
	printf("2147483648: %d\n", ft_atoi("2147483647"));
	printf("orig,intmx: %d\n\n", atoi("2147483647"));
	printf("-2147483648: %d\n", ft_atoi("-2147483648"));
	printf("atoi(intmn): %d\n", atoi("-2147483648"));
	printf("      -123: %d\n", ft_atoi("-123"));
	printf("     ab123: %d\n", ft_atoi("ab123"));
	printf(" 123abc123: %d\n", ft_atoi("123abc123"));
	printf("      +123: %d\n", ft_atoi("+123"));
	printf("    \"  123: %d\n", ft_atoi("  123"));
	printf("       001: %d\n", ft_atoi("001"));
	printf("        -0: %d\n", ft_atoi("-0"));
}
*/
