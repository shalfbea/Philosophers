/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:24:22 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/05 21:52:29 by shalfbea         ###   ########.fr       */
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

static int	ft_atoi_mod(const char *str, int *error)
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
	if (str[i] || sign == -1)
		(*error) = 1;
	return ((int) res * sign);
}

t_philo_info	parser(int argc, char **argv)
{
	t_philo_info	philo_info;
	int				i;
	char			*forks_free;

	if (argc < 5 || argc > 6)
		exitter(NULL, 1);
	i = 0;
	philo_info.num = ft_atoi_mod(argv[1], &i);
	philo_info.die = ft_atoi_mod(argv[2], &i);
	philo_info.eat = ft_atoi_mod(argv[3], &i);
	philo_info.sleep = ft_atoi_mod(argv[4], &i);
	philo_info.times_must_eat = 0;
	if (argc > 5)
		philo_info.times_must_eat = ft_atoi_mod(argv[5], &i);
	//if (i || philo_info.num <= 0 || philo_info.die <= 0 || philo_info.eat <= 0 || philo_info.sleep <= 0 || philo_info.times_must_eat <= 0)
	if (i)
		philo_info.num = 0;
	forks_free = (char *)malloc(sizeof(char) * philo_info.num);
	if (!forks_free)
		exitter(NULL, 1);
	i = -1;
	while (++i < philo_info.num)
		forks_free[i] = 1;
	philo_info.forks_free = forks_free;
	philo_info.finish = 0;
	pthread_mutex_init(&(philo_info.eat_mutex), NULL);
	return (philo_info);
}
