/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 22:41:31 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/09/27 23:13:41 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	exception_handler(t_philo *philo)
{
	if (philo->l_fork == philo->r_fork)
	{
		pthread_mutex_lock(philo->l_fork);
		if (print_msg(philo, FORK) == 1)
			return (1);
		while (*(philo->data->death) == 0)
		{
			if (get_time() - philo->last_eat
				> (unsigned long)philo->data->time_to_die)
			{
				pthread_mutex_unlock(philo->l_fork);
				return (1);
			}
		}
	}
	return (0);
}

static void	drop_the_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static int	grap_the_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (print_msg(philo, FORK) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	if (print_msg(philo, FORK) == 1)
	{
		drop_the_fork(philo);
		return (1);
	}
	return (0);
}

static int	eat(t_philo *philo)
{
	if (grap_the_fork(philo) == 1)
		return (1);
	if (print_msg(philo, EAT) == 1)
	{
		drop_the_fork(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->eat);
	philo->eat_count++;
	philo->last_eat = get_time();
	while ((int)(get_time() - philo->last_eat) < philo->data->time_to_eat)
		usleep(500);
	if (philo->eat_count == philo->data->must_eat_cnt)
	{
		pthread_mutex_unlock(&philo->eat);
		drop_the_fork(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat);
	drop_the_fork(philo);
	return (0);
}

void	*run_thread(void *philo_tmp)
{
	t_philo	*philo;
	int		tmp_sleep;

	philo = philo_tmp;
	if (exception_handler(philo) == 1)
		return (0);
	if (philo->num % 2 == 0)
		usleep(philo->data->time_to_eat);
	while (*(philo->data->death) == 0)
	{
		if (eat(philo) == 1)
			break ;
		if (print_msg(philo, SLEEP) == 1)
			break ;
		tmp_sleep = get_time();
		while ((int)(get_time() - tmp_sleep) < philo->data->time_to_sleep)
			usleep(500);
		if (print_msg(philo, THINK) == 1)
			break ;
	}
	return (0);
}
