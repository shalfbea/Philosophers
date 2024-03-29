/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:42:54 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/13 14:53:49 by shalfbea         ###   ########.fr       */
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

void	log_message(t_philo *philo, char mode)
{
	static char	first_die;

	pthread_mutex_lock(philo->info->death_mutex);
	if (philo->info->finish && mode != DIED && mode != EATING)
	{
		pthread_mutex_unlock(philo->info->death_mutex);
		return ;
	}
	pthread_mutex_unlock(philo->info->death_mutex);
	if (mode == 10)
		printf("%lld %d:started thread\n", time_getter(), philo->num);
	else if (mode == TAKEN_A_FORK)
		printf("%lld %d had taken a fork\n", time_getter(), philo->num);
	else if (mode == EATING && !first_die)
		printf("%lld %d is eating\n", time_getter(), philo->num);
	else if (mode == SLEEPING)
		printf("%lld %d is sleeping\n", time_getter(), philo->num);
	else if (mode == THINKING)
		printf("%lld %d is thinking\n", time_getter(), philo->num);
	else if (mode == DIED && !first_die)
	{
		printf("%lld %d died\n", time_getter(), philo->num);
		first_die = 1;
	}
}

int	exitter(t_philo *philoes, char mode)
{
	int	i;

	if (mode)
		printf("Error\n");
	if (!philoes)
		return (mode);
	i = -1;
	pthread_mutex_destroy(philoes->info->death_mutex);
	if (philoes->info->death_mutex)
		free (philoes->info->death_mutex);
	while (++i < philoes->info->num)
	{
		pthread_mutex_destroy(philoes[i].own_fork);
		pthread_mutex_destroy(philoes[i].meal_mutex);
		if (philoes[i].own_fork)
			free(philoes[i].own_fork);
		if (philoes[i].meal_mutex)
			free(philoes[i].meal_mutex);
	}
	if (philoes)
		free(philoes);
	return (mode);
}

void	threads_creator(t_philo *philoes)
{
	pthread_t		control_thread;
	int				i;

	i = -1;
	while (++i < philoes->info->num)
	{
		pthread_create(&philoes[i].thread, NULL, philo_life,
			(void *) &philoes[i]);
		philoes[i].last_fed = time_getter();
	}
	pthread_create(&control_thread, NULL, philo_control,
		(void *) philoes);
	pthread_join(control_thread, NULL);
	i = -1;
	while (++i < philoes->info->num)
		pthread_join(philoes[i].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;
	t_philo			*philoes;

	philo_info = parser(argc, argv);
	philoes = NULL;
	if (philo_info.num == 0)
		return (exitter(philoes, 1));
	philoes = philo_setter(&philo_info);
	if (!philoes)
		return (exitter(philoes, 1));
	threads_creator(philoes);
	return (exitter(philoes, 0));
}
