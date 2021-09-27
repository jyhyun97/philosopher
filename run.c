#include "philo.h"

void	*run_thread(void *philo_tmp)
{
    t_philo *philo;

    philo = philo_tmp;

    if (philo->l_fork == philo->r_fork)
    {
        pthread_mutex_lock(philo->l_fork); //포크 집기
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
        pthread_mutex_lock(philo->l_fork);//포크 집기
		print_msg(philo, FORK);
        pthread_mutex_lock(philo->r_fork);
		print_msg(philo, FORK);

        print_msg(philo, EAT);//먹기
        pthread_mutex_lock(&philo->eat);
        philo->eat_count++;
        philo->last_eat = get_time();
        if (philo->eat_count == philo->data->must_eat_cnt)
        {
            pthread_mutex_unlock(&philo->eat);
            pthread_mutex_unlock(philo->l_fork); //포크 놓기
            pthread_mutex_unlock(philo->r_fork);
            break;
        }
        while (*(philo->data->death) == 0 && get_time()
            - philo->last_eat < (unsigned long)philo->data->time_to_eat)
        {
        }
        pthread_mutex_unlock(&philo->eat);

        pthread_mutex_unlock(philo->l_fork);//포크 놓기
        pthread_mutex_unlock(philo->r_fork);

        unsigned long sleep_tmp;//자기
        print_msg(philo, SLEEP);
        sleep_tmp = get_time();
        while (*(philo->data->death) == 0 && get_time() - sleep_tmp < (unsigned long)philo->data->time_to_sleep)
        {
        }
        print_msg(philo, THINK);//생각하기
        usleep(100);
    }
    return (0);
    //짝수 재우기..
    //while (1)
    //포크 쥐기
    //먹기
    //포크 놓기
    //자기
    //생각하기
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
    //eat 동시에 죽기 방지..
}