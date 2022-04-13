/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:42:54 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/13 15:27:15 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	sem_wait(philo->info->logging_sem);
	if (philo->dead && mode != DIED && mode != EATING)
	{
		sem_post(philo->info->logging_sem);
		return ;
	}
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
	sem_post(philo->info->logging_sem);
}

static void	threads_starter(t_philo *philoes)
{
	int	i;

	i = -1;
	while (++i < philoes->info->num)
	{
		philoes[i].pid = fork();
		if (philoes[i].pid < 0)
			exitter(philoes, 1);
		if (philoes[i].pid == 0)
		{
			sem_wait(philoes[i].info->eat_sem);
			philo_life(&philoes[i]);
			exitter(philoes, 0);
		}
	}
	usleep(500);
}

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;
	t_philo			*philoes;

	philo_info = parser(argc, argv);
	philoes = NULL;
	if (philo_info.num == 0)
		exitter(philoes, 1);
	philoes = philo_setter(&philo_info);
	if (!philoes)
		exitter(philoes, 1);
	time_getter();
	threads_starter(philoes);
	exitter(philoes, 0);
}
