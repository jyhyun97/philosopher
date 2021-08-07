/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:54:16 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/08/06 17:02:05 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_eat(t_philo *philo)
{
	if (*(philo->data->death) == 0 && philo->num % 2 == 1)
	{
		if (*(philo->data->death) == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			print_msg(philo, FORK);
		}
		else
			return (1);
		if (*(philo->data->death) == 0)
		{
			pthread_mutex_lock(philo->r_fork);
			print_msg(philo, FORK);
		}
		else
		{
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}
	}
	else if (*(philo->data->death) == 0)
	{
		if (*(philo->data->death) == 0)
		{
			pthread_mutex_lock(philo->r_fork);
			print_msg(philo, FORK);
		}
		else
			return (1);
		if (*(philo->data->death) == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			print_msg(philo, FORK);
		}
		else
		{
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
	}
	if (*(philo->data->death) == 0)
		print_msg(philo, EAT);
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	philo->eat_count++;
	if (philo->eat_count == philo->data->must_eat_cnt)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (2);
	}
	philo->last_eat = get_time();
	while (*(philo->data->death) == 0 && get_time()
		- philo->last_eat < (unsigned long)philo->data->time_to_eat)
	{
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	do_sleep(t_philo *philo)
{
	unsigned long	sleep_tmp;

	if (*(philo->data->death) == 0)
		print_msg(philo, SLEEP);
	else
		return (1);
	sleep_tmp = get_time();
	while (*(philo->data->death) == 0 && get_time()
		- sleep_tmp < (unsigned long)philo->data->time_to_sleep)
	{
	}
	return (0);
}

int	do_think(t_philo *philo)
{
	if (*(philo->data->death) == 0)
		print_msg(philo, THINK);
	else
		return (1);
	return (0);
}

void	*run_thread(void *philo_tmp)
{
	t_philo	*philo;
	int		eat_tmp;

	philo = philo_tmp;
	if (philo->data->must_eat_cnt == 0)
		return (0);
	if (philo->data->num_of_philo < 2)
	{
		*(philo->data->death) = 1;
		philo->my_death = 1;
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
		eat_tmp = do_eat(philo);
		if (eat_tmp == 1)
			break ;
		else if (eat_tmp == 2)
			return (0);
		if (do_sleep(philo) == 1)
			break ;
		if (do_think(philo) == 1)
			break ;
	}
	return (0);
}

void	*run_monitor(void *philo_tmp)
{
	t_philo	*philo;

	philo = philo_tmp;
	while (*(philo->data->death) == 0 && philo->my_death == 0
		&& philo->data->must_eat_cnt != philo->eat_count)
	{
		if (philo->data->must_eat_cnt != philo->eat_count && get_time()
			- philo->last_eat > (unsigned long)philo->data->time_to_die)
		{
			*(philo->data->death) += 1;
			philo->my_death = 1;
		}
		usleep(100);
	}
	if (*(philo->data->death) == 1)
		print_msg(philo, DIE);
	return (0);
}
