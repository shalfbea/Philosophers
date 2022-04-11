/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:01:02 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/11 14:38:31 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	smart_sleeper(uint64_t milliseconds)
{
	uint64_t	start;

	start = time_getter();
	while (time_getter() - start < milliseconds)
		usleep(50);
}

char	eating(t_philo *philo)
{
	if (philo->info->num == 1)
		philo->dead = 1;
	sem_wait(philo->info->final_sem);
	if (philo->dead)
	{
		sem_post(philo->info->final_sem);
		return (1);
	}
	sem_post(philo->info->final_sem);
	sem_wait(philo->info->forks_sem);
	log_message(philo, TAKEN_A_FORK);
	sem_wait(philo->info->forks_sem);
	log_message(philo, TAKEN_A_FORK);
	sem_wait(philo->info->meal_sem);
	log_message(philo, EATING);
	philo->last_fed = time_getter();
	sem_post(philo->info->meal_sem);
	smart_sleeper(philo->info->eat);
	sem_post(philo->info->forks_sem);
	sem_post(philo->info->forks_sem);
	philo->times_eat++;
	return (0);
}

static void	*checker_thread(void *philosopher)
{
	t_philo	*philoe;

	philoe = (t_philo *) philosopher;
	while (1)
	{
		if ((time_getter()) - philoe->last_fed > philoe->info->die)
		{
			log_message(philoe, DIED);
			sem_wait(philoe->info->final_sem);
			philoe->dead = 1;
			sem_post(philoe->info->final_sem);
			sem_wait(philoe->info->logging_sem);
			exit(1);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}

void	philo_life(void *philosopher)
{
	t_philo		*philo;
	pthread_t	control_thread;

	philo = (t_philo *) philosopher;
	pthread_create(&control_thread, NULL, checker_thread,
		(void *) philo);
	philo->last_fed = time_getter();
	while (!philo->dead)
	{
		if (eating(philo))
			break ;
		if (philo->times_eat >= philo->info->times_must_eat
			&& philo->info->times_must_eat)
			break ;
		log_message(philo, SLEEPING);
		sem_wait(philo->info->final_sem);
		if (philo->dead)
		{
			sem_post(philo->info->final_sem);
			break ;
		}
		sem_post(philo->info->final_sem);
		smart_sleeper(philo->info->sleep);
		log_message(philo, THINKING);
	}
	sem_wait(philo->info->final_sem);
	if (philo->dead)
	{
		sem_post(philo->info->final_sem);
		exit(1);
	}
	sem_post(philo->info->final_sem);
	exit(0);
}
