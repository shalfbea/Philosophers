/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:26:42 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/05 21:57:16 by shalfbea         ###   ########.fr       */
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
	char			finish;
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				times_must_eat;
	char			*forks_free;
	pthread_mutex_t	eat_mutex;
}	t_philo_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				num;
	uint64_t		last_fed;
	char			dead;
	int				times_eat;
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
void			ft_putnbr(int n);
//philo_life.c
void			*philo_life(void *philosopher);
//main.c
void			log_message(t_philo *philo, char mode);
uint64_t		time_getter(void);
int				exitter(t_philo *philoes, char mode);
#endif
