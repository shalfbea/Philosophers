/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:01:02 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/05 22:04:58 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	smart_sleeper(t_philo_info *info, uint64_t milliseconds)
{
	uint64_t	start;

	start = time_getter();
	while (time_getter() - start < milliseconds)
	{
		if (info->finish == info->num)
			return (1);
		usleep(100);
	}
	return (0);
}

char	take_forks(t_philo *philo, int left, int right)
{
	char	took;

	took = 0;
	while(!took)
	{
		if (philo->info->finish == philo->info->num)
			return (1);
		pthread_mutex_lock(&(philo->info->eat_mutex));
		if (philo->info->forks_free[left] && philo->info->forks_free[right])
		{
			philo->info->forks_free[left] = 0;
			log_message(philo, TAKEN_A_FORK);
			philo->info->forks_free[right] = 0;
			log_message(philo, TAKEN_A_FORK);
			took = 1;
		}
		pthread_mutex_unlock(&(philo->info->eat_mutex));
		usleep(10);
	}
	return (0);
}

char	forks_back(t_philo *philo, int left, int right)
{
	if (philo->info->finish == philo->info->num)
		return (1);
	pthread_mutex_lock(&(philo->info->eat_mutex));
	philo->info->forks_free[left] = 1;
	philo->info->forks_free[right] = 1;
	pthread_mutex_unlock(&(philo->info->eat_mutex));
	return (0);
}

char	eating(t_philo *philo)
{
	int			left;
	int			right;

	if (philo->num == 1)
		left = philo->info->num - 1;
	else
		left = philo->num - 2;
	if (philo->num == philo->info->num)
		right = 0;
	else
		right = philo->num;
	if (take_forks(philo, left, right))
		return (1);
	if (time_getter() - (uint64_t) philo->last_fed > (uint64_t) philo->info->die)
	{
		log_message(philo, DIED);
		philo->dead = 1;
		philo->info->finish = philo->info->num;
	}
	else
	{
		log_message(philo, EATING);
		if (smart_sleeper(philo->info, philo->info->eat))
			return (1);
		philo->last_fed = time_getter();
	}
	if (forks_back(philo, left, right))
		return (1);
	if (philo->times_eat != -1)
		philo->times_eat++;
	if (philo->info->times_must_eat > 0 && philo->times_eat >= philo->info->times_must_eat)
	{
		//That's current problem. Put a mutex here?
		philo->info->finish ++;
		philo->times_eat = -1;
	}
	return (0);
}

void	*philo_life(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *) philosopher;
	philo->last_fed = time_getter();
	while (!philo->dead)
	{
		log_message(philo, SLEEPING);
		if (smart_sleeper(philo->info, philo->info->sleep))
			return (NULL);
		log_message(philo, THINKING);
		if (eating(philo))
			return (NULL);
	}
	return (NULL);
}
