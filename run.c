#include "philo.h"

int     exception_handler(t_philo *philo)
{
    if (philo->l_fork == philo->r_fork)
    {
        pthread_mutex_lock(philo->l_fork);
        if (print_msg(philo, FORK) == 1)
            return (1);
        while (*(philo->data->death) == 0)
        {
            if (get_time() - philo->last_eat > (unsigned long)philo->data->time_to_die)
            {
                pthread_mutex_unlock(philo->l_fork);
                return (1);
            }
        }
    }
	if (philo->num % 2 == 0)
	{
		while (*(philo->data->death) == 0 && get_time()
			- philo->last_eat < (unsigned long)philo->data->time_to_eat)
		{
		}
	}
    return (0);
}

void    drop_the_fork(t_philo *philo)
{
    pthread_mutex_unlock(&philo->eat);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void	*run_thread(void *philo_tmp)
{
    t_philo *philo;
    
    philo = philo_tmp;
    if (exception_handler(philo) == 1)
        return (0);
    while (*(philo->data->death) == 0)
    {
        pthread_mutex_lock(philo->l_fork);
		if (print_msg(philo, FORK) == 1)
        {
            pthread_mutex_unlock(philo->l_fork);
            break;
        }
        pthread_mutex_lock(philo->r_fork);
		if (print_msg(philo, FORK) == 1)
        {
            pthread_mutex_unlock(philo->l_fork);
            pthread_mutex_unlock(philo->r_fork);
            break;
        }
        if (print_msg(philo, EAT) == 1)
        {
            pthread_mutex_unlock(philo->l_fork);
            pthread_mutex_unlock(philo->r_fork);
            break;
        }
        pthread_mutex_lock(&philo->eat);
        philo->eat_count++;
        philo->last_eat = get_time();
        usleep(philo->data->time_to_eat * 1000);
        if (philo->eat_count == philo->data->must_eat_cnt)
        {
            drop_the_fork(philo);
            break;
        }
        drop_the_fork(philo);

        if (print_msg(philo, SLEEP) == 1)
            break;
        usleep(philo->data->time_to_sleep * 1000);
        if (print_msg(philo, THINK) == 1)
            break;
        usleep(10);
    }
    return (0);
}

void	*run_monitor(void *philo_tmp)
{
    t_philo *philo;

    philo = philo_tmp;

    while (*(philo->data->death) == 0 && philo->my_death == 0
		&& philo->data->must_eat_cnt != philo->eat_count)
	{
		if (philo->data->must_eat_cnt != philo->eat_count && get_time()
			- philo->last_eat > (unsigned long)philo->data->time_to_die)
		{
            pthread_mutex_lock(&philo->eat);
			*(philo->data->death) += 1;
			philo->my_death = 1;
            pthread_mutex_unlock(&philo->eat);
		}
		usleep(100);
	}
	if (*(philo->data->death) == 1)
		print_msg(philo, DIE);
	return (0);
}