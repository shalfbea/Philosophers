# Philosophers

I never thought philosophy would be so deadly

## About

This project is part of program in [School 21](https://21-school.ru/) ([Ecole 42](42.fr)).
That's my solution for the dining philosophers problem
The main goal of this project is to learn how the threads
and processes work

## Requirements

- GNU GCC
- GNU Make

## Installation and usage

1. Download/Clone this repo

   > git clone https://github.com/shalfbea/Philosophers

2. Get into the root directory of project and then choose usual
	or bonus folder and run make
   > cd philo (philo_bonus)
   > make

3. Now you are ready to test the program with the following arguments:
	> ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <[number_of_times_each_philosopher_must_eat]>

Where :
- number_of_philosophers: The number of philosophers and also the number
of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds
since the beginning of their last meal or the beginning of the simulation, they die.
-  time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all philosophers
have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

## Technical task

The full task can be found here: [philosophers_subject](https://github.com/shalfbea/Philosophers/blob/main/philosophers_subject.pdf)

### Quick summary:

- Only using c language is allowed
- Code-style should respect the [The Norm](https://github.com/MagicHatJo/-42-Norm/blob/master/norme.en.pdf)
- No memory leaks, segmentation faults, undefined behavior
- Only allowed functions: memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there
are several philosophers, each philosopher has a fork on their left side
and a fork on their right side. If there is only one philosopher, there should
be only one fork on the table.
• To prevent philosophers from duplicating forks, you should protect the
forks state with a mutex for each of them.
### Bonus:

- Allowed functions: memset, printf, malloc, free, write, fork, kill,
exit, pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday, waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink
- Different rules from mandatory:
  - All the forks are put in the middle of the table.
  - They have no states in memory but the number of available forks is represented by a semaphore.
  - Each philosopher should be a process. But the main process should not be a philosopher.

### Evaluation result:
<img width="1591" alt="Screen Shot 2022-09-14 at 18 47 55" src="https://user-images.githubusercontent.com/92727363/190201894-3cb184f8-81a0-4b4c-abb9-42c0b9d24252.png">
