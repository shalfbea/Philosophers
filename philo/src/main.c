/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:42:54 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/07 22:01:41 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	time_getter(void)
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
	//pthread_mutex_lock(&(philo->info->logging_mutex));
	if (philo->info->finish && mode != EATING)
	{
		//pthread_mutex_unlock(&(philo->info->logging_mutex));
		return ;
	}
		//printf("Lol someone dead but Im chatting! %d %d\n", philo->num, mode) ;
	if (mode == 10)
		printf("%lld %d:started thread\n", time_getter(), philo->num);
	else if (mode == TAKEN_A_FORK)
		printf("%lld %d had taken a fork\n", time_getter(), philo->num);
	else if (mode == EATING)
		printf("%lld %d is eating\n", time_getter(), philo->num);
		//printf("%lld %d is eating <====================\n", time_getter(), philo->num);
	else if (mode == SLEEPING)
		printf("%lld %d is sleeping\n", time_getter(), philo->num);
	else if (mode == THINKING)
		printf("%lld %d is thinking\n", time_getter(), philo->num);
	else if (mode == DIED)
		//printf("\n==============================================================\n%lld %d died\n", time_getter(), philo->num);
		printf("%lld %d died\n", time_getter(), philo->num);
	//pthread_mutex_unlock(&(philo->info->logging_mutex));
}

int	exitter(t_philo *philoes, char mode)
{
	int	i;

	if (mode)
		printf("Exit because of an error");
	if (!philoes)
		return (mode);
	if (philoes->info->num != 1)
	{
		i = -1;
		while (++i < philoes->info->num)
		{
			pthread_mutex_destroy(philoes[i].own_fork);
			pthread_mutex_destroy(philoes[i].neigbor_fork);
			pthread_mutex_destroy(&(philoes[i].meal_mutex));
			//if (philoes[i].own_fork)
			//	free(philoes[i].own_fork);
			//if (philoes[i].neigbor_fork)
			//	free(philoes[i].neigbor_fork);
		}
	}
	if (philoes)
		free(philoes);
	pthread_mutex_destroy(&(philoes->info->finished_mutex));
	pthread_mutex_destroy(&(philoes->info->logging_mutex));
	return (mode);
}

void	forks_initter(t_philo *philoes)
{
	int				i;

	i = -1;
	if (philoes->info->num == 1)
	{
		philoes[0].own_fork = NULL;
		return ;
	}
	while (++i < philoes->info->num)
	{
		philoes[i].own_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philoes[i].own_fork, NULL);
	}
	i = -1;
	while (++i < philoes->info->num)
	{
		philoes[i].neigbor_fork = philoes[(i + 1) % philoes->info->num].own_fork;
	}
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
		if (i != philo_info->num - 1)
			philoes[i].next = &philoes[i+1];
	}
	forks_initter(philoes);
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
		//log_message(&philoes[i], 10);
		philoes[i].last_fed = time_getter();//+ philo_info->eat;
		//usleep(50);
	}
	i = -1;
	pthread_t		control_thread;
	pthread_create(&control_thread, NULL, philo_control,
			(void *) philoes);
	pthread_join(control_thread, NULL);//(void **) &status_adr);
	/*
	while (++i < philo_info.num)
	{
		pthread_join(philoes[i].thread, NULL);//(void **) &status_adr);
	}
	*/
	//printf("philoes finished %d", philo_info.finish);
	usleep(1000);
	exitter(philoes, 0);
	return (0);
}
