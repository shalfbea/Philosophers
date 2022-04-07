/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:01:02 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/07 21:59:12 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	check_die(t_philo *philo)
{
	if (time_getter() - (uint64_t) philo->last_fed > (uint64_t) philo->info->die)
	{
		log_message(philo, DIED);
		philo->dead = 1;
		pthread_mutex_lock(&(philo->info->finished_mutex));
		philo->info->finish = philo->info->num;
		pthread_mutex_unlock(&(philo->info->finished_mutex));
		return (1);
	}
	return (0);
}

void	smart_sleeper(uint64_t milliseconds)
{
	uint64_t	start;

	start = time_getter();
	while (time_getter() - start < milliseconds)
	{
		//if (philo->info->finish >= philo->info->num)
		//	return (1);
		usleep(50);
	}
}

//rewrite using uniqle mutexes
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->own_fork);
	log_message(philo, TAKEN_A_FORK);
	pthread_mutex_lock(philo->neigbor_fork);
	log_message(philo, TAKEN_A_FORK);
}
//rewrite
void forks_back(t_philo *philo)
{
	pthread_mutex_unlock(philo->own_fork);
	pthread_mutex_unlock(philo->neigbor_fork);
}

char	eating(t_philo *philo)
{
	if (philo->info->num == 1)
		return (1);
	if(philo->info->finish)
		return (1);
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	log_message(philo, EATING);
	philo->last_fed = time_getter();
	pthread_mutex_unlock(&philo->meal_mutex);
	smart_sleeper(philo->info->eat);
	//philo->last_fed = time_getter() + philo->info->eat;
	forks_back(philo);
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
		if (philo->info->finish)
			return (NULL);
		log_message(philo, SLEEPING);
		smart_sleeper(philo->info->sleep);
		log_message(philo, THINKING);
	}
	return (NULL);
}
