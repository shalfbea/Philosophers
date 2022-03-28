/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:42:54 by shalfbea          #+#    #+#             */
/*   Updated: 2022/03/28 17:54:21 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void log_message(int philo_num, char mode)
{
	// print timestamp;
	if (mode < 1 || mode > 5)
		return ;
	ft_putnbr(philo_num);
	if (mode == TAKEN_A_FORK)
		write(1, " has taken a fork\n", 19);
	else if (mode == EATING)
		write(1, " is eating\n", 12);
	else if (mode == SLEEPING)
		write(1, " is sleeping\n", 14);
	else if (mode == THINKING)
		write(1, " is thinking\n", 13);
	else if (mode == DIED)
		write(1, " died\n", 7);
}

void	*test(void *philo)
{
	printf("%d: I am a philo!\n",((t_philo*) philo)->num);
	return (NULL);
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
		philoes[i].num = i + 1;
	i = -1;
	while (++i < philo_info.number_of_philosophers)
	{
		pthread_create(&philoes[i].thread, NULL, test, (void *) &philoes[i]);
	}
	i = -1;
	status_adr = 0;
	while (++i < philo_info.number_of_philosophers)
	if(1)
	{
		printf("trying : %d\n", i);
		status = pthread_join(philoes[i].thread, NULL);//(void **) &status_adr);
		if (status)
			printf("ERROR: cant join thread, status = %d\n", status);
		else
			printf("i: %d, status addr: %d\n", i, status_adr);
	}
	if (philoes)
		free(philoes);
	return (0);
}
