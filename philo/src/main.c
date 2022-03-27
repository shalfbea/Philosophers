/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:42:54 by shalfbea          #+#    #+#             */
/*   Updated: 2022/03/27 20:41:31 by shalfbea         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;

	philo_info = parser(argc, argv);
	for (int i = 1; i < 6; ++i)
		log_message(1, i);
	return (0);
}
