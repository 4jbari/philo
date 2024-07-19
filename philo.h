#ifndef PHILO_H
#define PHILO_H


// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



typedef struct s_philo{

    int             id;
    pthread_mutex_t L_fork;
    pthread_mutex_t R_fork;



} philo_t;


typedef struct s_data
{
    long            num_of_philos;
    long            time2die;
    long            time2eat;
    long            time2sleep;
    long            num_of_meals;
    philo_t         *philo;
    pthread_mutex_t *forks;
} data_t;


#endif
