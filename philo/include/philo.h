/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:26:42 by shalfbea          #+#    #+#             */
/*   Updated: 2022/03/30 19:37:43 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct timeval	t_timeval;

typedef struct s_philo_info
{
	int			number_of_philosophers;
	int			die;
	int			eat;
	int			sleep;
	int			times_must_eat;
	//t_timeval	start;
	uint64_t	start_timer;
}	t_philo_info;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	num;
	char			fork_in_use;
	t_philo_info	*info;
}	t_philo;

# define TAKEN_A_FORK 1
# define EATING	2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

//parser.c
t_philo_info	parser(int argc, char **argv);
//utils.c
void	ft_putnbr(int n);
//philo_life.c
void	*philo_life(void *philosopher);
//main.c
void log_message(t_philo *philo, char mode);
uint64_t	time_getter(void);
#endif
