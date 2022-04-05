/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:42:54 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/05 22:03:10 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	time_getter(void)
{
	t_timeval			tmp;
	static uint64_t		start;
	uint64_t			result;

	if (!start)
	{
		gettimeofday(&tmp, NULL);
		start = tmp.tv_sec * 1000 + tmp.tv_usec / 1000.0;
	}
	gettimeofday(&tmp, NULL);
	result = tmp.tv_sec * 1000 + tmp.tv_usec / 1000.0 - start;
	return (result);
}

void log_message(t_philo *philo, char mode)
{
	//if (mode < 1 || mode > 5)
	//	return ;
	if (philo->info->finish)
		return ;
		//printf("Lol someone dead but Im chatting! %d %d\n", philo->num, mode) ;
	if (mode == 10)
		printf("%lld %d:started thread\n", time_getter(), philo->num);
	else if (mode == TAKEN_A_FORK)
		printf("%lld %d had taken a fork\n", time_getter(), philo->num);
	else if (mode == EATING)
		printf("%lld %d is eating\n", time_getter(), philo->num);
	else if (mode == SLEEPING)
		printf("%lld %d is sleeping\n", time_getter(), philo->num);
	else if (mode == THINKING)
		printf("%lld %d is thinking\n", time_getter(), philo->num);
	else if (mode == DIED)
		//printf("\n==============================================================\n%lld %d died\n", time_getter(), philo->num);
		printf("%lld %d died\n", time_getter(), philo->num);
}

int	exitter(t_philo *philoes, char mode)
{
	if (mode)
		printf("Exit because of an error");
	if (!philoes)
		return (mode);
	if (philoes->info->forks_free)
		free(philoes->info->forks_free);
	if (philoes)
		free(philoes);
	pthread_mutex_destroy(&(philoes->info->eat_mutex));
	return (mode);
}

t_philo	*philo_setter(t_philo_info *philo_info)
{
	t_philo	*philoes;
	int		i;

	philoes = (t_philo *)malloc(sizeof(t_philo) * philo_info->num);
	if (!philoes)
		exitter(philoes, 1);
	i = -1;
	while (++i < philo_info->num)
	{
		philoes[i].num = i + 1;
		philoes[i].info = philo_info;
		philoes[i].dead = 0;
		philoes[i].times_eat = 0;
	}

	return (philoes);
}

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;
	t_philo			*philoes;
	int				i;

	philo_info = parser(argc, argv);
	if (philo_info.num == 0)
		return (0);
	philoes = philo_setter(&philo_info);
	i = -1;
	time_getter(); //Don't forget to call it!
	while (++i < philo_info.num)
	{
		pthread_create(&philoes[i].thread, NULL, philo_life,
			(void *) &philoes[i]);
		log_message(&philoes[i], 10);
	}
	i = -1;
	while (++i < philo_info.num)
	{
		pthread_join(philoes[i].thread, NULL);//(void **) &status_adr);
	}
	printf("philoes finished %d", philo_info.finish);
	exitter(philoes, 0);
	return (0);
}
