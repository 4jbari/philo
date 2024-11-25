#ifndef PHILO_H
# define PHILO_H

// LIBRARIES
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

// MACROS
# define FORK   0
# define EAT    1
# define SLEEP  2
# define THINK  3
# define DEAD   4

# define BREAK	1

typedef struct s_data
{
	long			num_of_philos;
	long			time2die;
	long			time2eat;
	long			time2sleep;
	long			num_of_meals;
	long			start_time;
	long			simu_done;

	pthread_mutex_t	meal_cnt_mtx;
	pthread_mutex_t	num_of_philos_mtx;//
	pthread_mutex_t	simu_done_mtx;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	long	id;
	long	l_fork;
	long	r_fork;
	long	died;
	long	meal_count;
	long	last_meal;
	t_data	*data;
}	t_philo;

// mutex_handlers
void	seter(pthread_mutex_t *mutex, long *var, long value);
long	geter(pthread_mutex_t *mutex, long *var);

// paraser
int		parsing(char **av, t_data *data);

// routine
void	routine(void *arg);

// monitor 
void	monitor(t_philo *philo, t_data *data);

// utils
long	get_time(void);

//print
void	print_fun(int flag, int id, t_data *data);

//initiator
int		init_philos(t_data *data, t_philo **philo);
int		init_forks(t_data *data);
int		init_threads(t_data *data, t_philo *philo);

#endif
