#include "philo.h"

void	*run_thread(void *philo_tmp)
{
    t_philo *philo;
    
    philo = philo_tmp;

    if (philo->l_fork == philo->r_fork)
    {
        pthread_mutex_lock(philo->l_fork);
        print_msg(philo, FORK);
        while (*(philo->data->death) == 0)
        {
            if (get_time() - philo->last_eat > (unsigned long)philo->data->time_to_die)
            {
                pthread_mutex_unlock(philo->l_fork);
                return (0);
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
    while (*(philo->data->death) == 0)
    {
        pthread_mutex_lock(philo->l_fork);
		print_msg(philo, FORK);
        pthread_mutex_lock(philo->r_fork);
		print_msg(philo, FORK);

        print_msg(philo, EAT);
        pthread_mutex_lock(&philo->eat);
        philo->eat_count++;
        philo->last_eat = get_time();
        usleep(philo->data->time_to_eat * 1000);
        if (philo->eat_count == philo->data->must_eat_cnt)
        {
            pthread_mutex_unlock(&philo->eat);
            pthread_mutex_unlock(philo->l_fork);
            pthread_mutex_unlock(philo->r_fork);
            break;
        }

        pthread_mutex_unlock(&philo->eat);
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);

        print_msg(philo, SLEEP);
        usleep(philo->data->time_to_sleep * 1000);
        print_msg(philo, THINK);
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