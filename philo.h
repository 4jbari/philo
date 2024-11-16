#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

//DEFINE MACROS

typedef struct s_data
{
    long            num_of_philos;
    long            time2die;
    long            time2eat;
    long            time2sleep;
    long            num_of_meals;
    long            start_time;
    int             simu_end;
    pthread_mutex_t simu_end_mtx;
    pthread_mutex_t last_meal;
    pthread_mutex_t print_mtx;
    pthread_mutex_t *forks;
} data_t;


typedef struct s_philo{

    int     id;
    int     l_fork;
    int     r_fork;
    int     died;
    long    last_meal;
    data_t  *data;
} philo_t;




#endif
