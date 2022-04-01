/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:42:54 by shalfbea          #+#    #+#             */
/*   Updated: 2022/03/30 19:44:37 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	time_getter(void)
{
	t_timeval		tmp;
	static uint64_t		start;
	uint64_t 		result;

	if (!start)
	{
		gettimeofday(&tmp, NULL);
		start = tmp.tv_sec * 1000 + tmp.tv_usec/1000.0;
	}
	gettimeofday(&tmp, NULL);
	result = tmp.tv_sec * 1000 + tmp.tv_usec/1000.0 - start;
	return (result);
}

void log_message(t_philo *philo, char mode)
{
	//if (mode < 1 || mode > 5)
	//	return ;
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
		printf("%lld %d died\n", time_getter(), philo->num);
}

int	main(int argc, char **argv)
{
	int				i;
	t_philo_info	philo_info;
	t_philo			*philoes;
	int				status_adr;
	int				status;

	status = 0;
	philo_info = parser(argc, argv);
	philoes = (t_philo *)malloc(sizeof(t_philo) * philo_info.number_of_philosophers);
	if (!philoes)
		exit(0);

	i = -1;
	while (++i < philo_info.number_of_philosophers)
	{
		philoes[i].num = i + 1;
		philoes[i].info = &philo_info;
	}
	i = -1;
	//very important to move code below!!!
	/*
	t_timeval		start_timer;
	gettimeofday(&start_timer, NULL);
	philo_info.start_timer = start_timer.tv_sec * 1000 + start_timer.tv_usec/1000.0
	*/
	time_getter();
	while (++i < philo_info.number_of_philosophers)
	{
		pthread_create(&philoes[i].thread, NULL, philo_life, (void *) &philoes[i]);
		log_message(&philoes[i], 10);
	}
	i = -1;
	status_adr = 0;
	while (++i < philo_info.number_of_philosophers)
	if(1)
	{
		status = pthread_join(philoes[i].thread, NULL);//(void **) &status_adr);
		/*
		if (status)
			printf("ERROR: cant join thread, status = %d\n", status);
		else
			printf("i: %d, status addr: %d\n", i, status_adr);
		*/
	}
	if (philoes)
		free(philoes);
	return (0);
}
