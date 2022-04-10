/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:23:17 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/10 21:03:07 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	rules_check(t_philo *philoe, int *fed_enough)
{
	pthread_mutex_lock(philoe->meal_mutex);
	if (philoe->times_eat >= philoe->info->times_must_eat
		&& philoe->info->times_must_eat)
		(*fed_enough)++;
	pthread_mutex_unlock(philoe->meal_mutex);
	if ((time_getter()) - philoe->last_fed > philoe->info->die)
	{
		log_message(philoe, DIED);
		philoe->info->finish = 1;
		return (1);
	}
	return (0);
}

void	*philo_control(void *philosophers)
{
	t_philo	*philoes;
	int		i;
	int		fed_enough;

	philoes = (t_philo *) philosophers;
	while (!(philoes->info->finish))
	{
		fed_enough = 0;
		i = -1;
		while (++i < philoes->info->num)
			rules_check(&philoes[i], &fed_enough);
		if (fed_enough == philoes->info->num && philoes->info->times_must_eat)
			philoes->info->finish = 1;
		usleep(10);
	}
	return (NULL);
}

static void	forks_initter(t_philo *philoes)
{
	int				i;

	i = -1;
	while (++i < philoes->info->num)
	{
		philoes[i].own_fork = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t));
		philoes[i].meal_mutex = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philoes[i].own_fork, NULL);
		pthread_mutex_init(philoes[i].meal_mutex, NULL);
	}
	i = -1;
	while (++i < philoes->info->num)
		philoes[i].neigbor_fork = philoes[(i + 1)
			% philoes->info->num].own_fork;
}

t_philo	*philo_setter(t_philo_info *philo_info)
{
	t_philo	*philoes;
	int		i;

	philoes = (t_philo *)malloc(sizeof(t_philo) * philo_info->num);
	if (!philoes)
		return (NULL);
	i = -1;
	while (++i < philo_info->num)
	{
		philoes[i].num = i + 1;
		philoes[i].info = philo_info;
		philoes[i].times_eat = 0;
	}
	forks_initter(philoes);
	return (philoes);
}
