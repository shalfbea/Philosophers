/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:24:22 by shalfbea          #+#    #+#             */
/*   Updated: 2022/03/27 19:00:15 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\r')
		return (1);
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	return (0);
}

static int	ft_atoi_helper(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-')
	{
		*sign = -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	return (i);
}

static int	ft_atoi(const char *str)
{
	size_t	res;
	int		i;
	int		sign;

	sign = 1;
	res = 0;
	i = ft_atoi_helper(str, &sign);
	while ((str[i]) >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - '0';
		++i;
		if ((sign > 0) && (res > 2147483647))
			return (-1);
		if ((sign < 0) && (res > 2147483648))
			return (0);
	}
	return ((int) res * sign);
}

t_philo_info	parser(int argc, char **argv)
{
	t_philo_info	philo_info;

	if (argc < 5 || argc > 6)
		exit(0);
	(void) argv;
	ft_atoi("kek");
	philo_info.number_of_philosophers = ft_atoi(argv[1]);
	philo_info.time_to_die = ft_atoi(argv[2]);
	philo_info.time_to_eat = ft_atoi(argv[3]);
	philo_info.time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		philo_info.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (philo_info);
}
