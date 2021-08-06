#ifndef PHILO_H
# define PHILO_H

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_cnt;
    int *death;
    unsigned long    start_time;
    pthread_mutex_t *print;
    pthread_mutex_t *fork;
}   t_data;

typedef struct s_philo
{
    int num;
    int eat_count;
    int my_death;
    unsigned long last_eat;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    pthread_t thread;
    pthread_t monitor;
    t_data  *data;
}   t_philo;

void free_data(t_data *data, t_philo *philo);

//init.c
int check_input(int argc, char *argv[]);
int malloc_data(char *argv[], t_data *data, t_philo **philo);
void init_data(char *argv[], t_data *data);
void init_philo(t_data *data,t_philo *philo);
void init_thread(t_data *data, t_philo *philo);

//util.c
void print_msg(t_philo *philo, int flag);
unsigned long get_time(void);
int ft_atoi(const char *str);
int ft_isdigit(char *s);

//run.c
void *run_thread(void *philo_tmp);
void *run_monitor(void *philo_tmp);

#endif