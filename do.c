/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 01:01:00 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/08/10 01:02:44 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	left_hand(t_philo *philo)
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
	return (0);
}

int	right_hand(t_philo *philo)
{
	if (*(philo->data->death) == 0 && philo->num % 2 == 0)
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
	return (0);
}

int	do_eat(t_philo *philo)
{
	if (left_hand(philo) == 1)
		return (1);
	if (right_hand(philo) == 1)
		return (1);
	if (*(philo->data->death) == 0)
		print_msg(philo, EAT);
	else
		drop_the_fork(philo);
	pthread_mutex_lock(philo->data->eat);
	philo->eat_count++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->data->eat);
	if (philo->eat_count == philo->data->must_eat_cnt)
	{
		drop_the_fork(philo);
		return (2);
	}
	while (*(philo->data->death) == 0 && get_time()
		- philo->last_eat < (unsigned long)philo->data->time_to_eat)
	{
	}
	drop_the_fork(philo);
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
