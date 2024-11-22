#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>

// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

// MACROS
#define FORK    0
#define EAT     1
#define SLEEP   2
#define THINK   3

#define BREAK	1



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
    pthread_mutex_t	num_of_philos_mtx;
    pthread_mutex_t	simu_done_mtx;
    pthread_mutex_t	last_meal;
    pthread_mutex_t	print_mtx;
    pthread_mutex_t	*forks;
} data_t;


typedef struct s_philo{

    long	id;
    long	l_fork;
    long	r_fork;
    long	died;
    long	meal_count;
    long	last_meal;
    data_t	*data;
} philo_t;


// mutex_handlers

// long	geter(pthread_mutex_t *mutex, long var);
// void 	seter(pthread_mutex_t *mutex, long *var, long value);


//tools
char	*ft_strtrim(char const *s1, char const *set);

#endif
