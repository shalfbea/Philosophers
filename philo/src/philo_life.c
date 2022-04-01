/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:01:02 by shalfbea          #+#    #+#             */
/*   Updated: 2022/03/30 19:41:23 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleeper(uint64_t milliseconds)
{
	uint64_t	start;

	start = time_getter();
	while (time_getter() - start < milliseconds)
	{
		usleep(100);
	}

}

void	*philo_life(void *philosopher)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *) philosopher;
	i = -1;
	while (++i < 10)
		//usleep(100000);
		smart_sleeper(1);
	//if (i == (int) philo->num)
		log_message(philo, 1);
	return (NULL);
}
