/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:23:17 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/07 20:47:10 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_control(void *philosophers)
{
	t_philo	*philoes;
	int		i;
	int		fed_enough;

	philoes = (t_philo *) philosophers;
	while (philoes->info->finish != philoes->info->num)
	{
		fed_enough = 0;
		i = -1;
		while (++i < philoes->info->num)
		{
			pthread_mutex_lock(&(philoes[i].meal_mutex));
			if (philoes[i].times_eat >= philoes->info->times_must_eat && philoes->info->times_must_eat)
				fed_enough++;
			pthread_mutex_unlock(&(philoes[i].meal_mutex));
			if ((time_getter()) - (philoes[i]).last_fed >  philoes[i].info->die)
			{
				log_message(&philoes[i], DIED);
				philoes[i].dead = 1;
				//pthread_mutex_lock(&(philoes[i].info->finished_mutex));
				philoes->info->finish = 1;
				printf("==========> DIE MTHF DIE %llu %llu", time_getter(), philoes[i].last_fed);
				//pthread_mutex_unlock(&(philoes[i].info->finished_mutex));
				return (NULL);
			}
		}
		if (fed_enough == philoes->info->num && philoes->info->times_must_eat)
		{
			philoes->info->finish = 1;
			return (NULL);
		}
	}
	i = -1;
	/*
	while (++i < philoes->info->num)
	{
		pthread_join(philoes[i].thread, NULL);//(void **) &status_adr);
	}
	*/
	return (NULL);
}
