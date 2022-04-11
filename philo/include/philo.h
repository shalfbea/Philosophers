/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:26:42 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/11 14:20:56 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;

typedef struct s_philo_info
{
	char			finish;
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				times_must_eat;
	pthread_mutex_t	*death_mutex;
}	t_philo_info;

typedef struct s_philo
{
	pthread_mutex_t	*own_fork;
	pthread_mutex_t	*neigbor_fork;
	pthread_t		thread;
	int				num;
	int64_t			last_fed;
	int				times_eat;
	pthread_mutex_t	*meal_mutex;
	t_philo_info	*info;
}	t_philo;

# define TAKEN_A_FORK 1
# define EATING	2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

t_philo_info	parser(int argc, char **argv);
void			*philo_life(void *philosopher);
void			log_message(t_philo *philo, char mode);
int64_t			time_getter(void);
int				exitter(t_philo *philoes, char mode);
void			*philo_control(void *philosophers);
t_philo			*philo_setter(t_philo_info *philo_info);
#endif
