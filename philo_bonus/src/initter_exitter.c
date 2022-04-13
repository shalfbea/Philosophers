/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initter_exitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:23:17 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/13 15:27:56 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	sem_initter(t_philo_info *info)
{
	sem_unlink("/philoes_meal");
	sem_unlink("/philoes_logging");
	sem_unlink("/philoes_forks");
	sem_unlink("/philoes_final");
	sem_unlink("/philoes_eat");
	info->meal_sem = sem_open("/philoes_meal", O_CREAT, S_IRWXU, 1);
	info->logging_sem = sem_open("/philoes_logging", O_CREAT, S_IRWXU, 1);
	info->final_sem = sem_open("/philoes_final", O_CREAT, S_IRWXU, 1);
	info->forks_sem = sem_open("/philoes_forks", O_CREAT, S_IRWXU, info->num);
	info->eat_sem = sem_open("/philoes_eat", O_CREAT, S_IRWXU, info->num);
	if (info->meal_sem <= 0 | info->logging_sem <= 0 | info->forks_sem <= 0
		| info->final_sem <= 0 | info->eat <= 0)
		return (1);
	return (0);
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
		philoes[i].times_eat = 0;
		philoes[i].dead = 0;
	}
	if (sem_initter(philoes->info))
		return (NULL);
	return (philoes);
}

void	*fed_control(void *philos_void)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *) philos_void;
	i = -1;
	while (++i < philos->info->num)
		sem_wait(philos->info->eat_sem);
	sem_wait(philos->info->logging_sem);
	i = -1;
	while (++i < philos->info->num)
		kill(philos[i].pid, SIGTERM);
	return (NULL);
}

static void	close_philo_sems(t_philo_info *info)
{
	sem_close(info->meal_sem);
	sem_close(info->logging_sem);
	sem_close(info->forks_sem);
	sem_close(info->final_sem);
	sem_unlink("/philoes_meal");
	sem_unlink("/philoes_logging");
	sem_unlink("/philoes_forks");
	sem_unlink("/philoes_final");
}

void	exitter(t_philo *philoes, char mode)
{
	int			i;
	pthread_t	fed_thread;

	if (mode)
		printf("Error\n");
	if (!philoes)
		exit(mode);
	pthread_create(&fed_thread, NULL, fed_control,
		(void *) philoes);
	waitpid(-1, NULL, 0);
	i = -1;
	while (++i < philoes->info->num)
		kill(philoes[i].pid, SIGTERM);
	close_philo_sems(philoes->info);
	if (philoes)
		free(philoes);
	exit (mode);
}
