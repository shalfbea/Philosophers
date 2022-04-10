/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:01:02 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/10 16:29:10 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleeper(uint64_t milliseconds)
{
	uint64_t	start;

	start = time_getter();
	while (time_getter() - start < milliseconds)
		usleep(50);
}

void	take_forks(t_philo *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->own_fork);
		log_message(philo, TAKEN_A_FORK);
		pthread_mutex_lock(philo->neigbor_fork);
		log_message(philo, TAKEN_A_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->neigbor_fork);
		log_message(philo, TAKEN_A_FORK);
		pthread_mutex_lock(philo->own_fork);
		log_message(philo, TAKEN_A_FORK);
	}
}

char	eating(t_philo *philo)
{
	if (philo->info->num == 1)
		return (1);
	if (philo->info->finish)
		return (1);
	take_forks(philo);
	pthread_mutex_lock(philo->meal_mutex);
	log_message(philo, EATING);
	philo->last_fed = time_getter();
	pthread_mutex_unlock(philo->meal_mutex);
	smart_sleeper(philo->info->eat);
	pthread_mutex_unlock(philo->own_fork);
	pthread_mutex_unlock(philo->neigbor_fork);
	philo->times_eat++;
	return (0);
}

void	*philo_life(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *) philosopher;
	philo->last_fed = time_getter();
	while (!philo->info->finish)
	{
		if (eating(philo))
			return (NULL);
		log_message(philo, SLEEPING);
		if (philo->info->finish)
			return (NULL);
		smart_sleeper(philo->info->sleep);
		log_message(philo, THINKING);
	}
	return (NULL);
}
