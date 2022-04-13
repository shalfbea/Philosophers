/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:26:42 by shalfbea          #+#    #+#             */
/*   Updated: 2022/04/13 13:58:12 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				times_must_eat;
	sem_t			*meal_sem;
	sem_t			*logging_sem;
	sem_t			*forks_sem;
	sem_t			*final_sem;
	sem_t			*eat_sem;
}	t_philo_info;

typedef struct s_philo
{
	pid_t			pid;
	int				num;
	int64_t			last_fed;
	int				times_eat;
	char			dead;
	t_philo_info	*info;
}	t_philo;

# define TAKEN_A_FORK 1
# define EATING	2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

t_philo_info	parser(int argc, char **argv);
void			philo_life(void *philosopher);
void			log_message(t_philo *philo, char mode);
int64_t			time_getter(void);
void			exitter(t_philo *philoes, char mode);
t_philo			*philo_setter(t_philo_info *philo_info);
void			*fed_control(void *philos_void);
#endif
