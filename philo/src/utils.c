/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:10:17 by shalfbea          #+#    #+#             */
/*   Updated: 2022/03/27 20:37:13 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	ft_putnbr_cases(int *n)
{
	if (*n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (1);
	}
	if (*n < 0)
	{
		write(1, "-", 1);
		*n *= -1;
	}
	return (0);
}

/*
** Outputs the integer ’n’ to the given file
** descriptor.
*/
void	ft_putnbr(int n)
{
	int		tmp;
	int		tens;
	char	cur;

	if (ft_putnbr_cases(&n))
		return ;
	tmp = n;
	tens = 1;
	while (tmp > 9)
	{
		tmp /= 10;
		tens *= 10;
	}
	while (tens > 0)
	{
		cur = (char)(n / tens) + '0';
		write(1, &cur, 1);
		n %= tens;
		tens /= 10;
	}
}
