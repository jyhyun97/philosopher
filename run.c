/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:54:16 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/08/10 01:04:43 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_the_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	main_loop(t_philo *philo)
{
	int	eat_tmp;

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

void	*run_thread(void *philo_tmp)
{
	t_philo	*philo;

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
	main_loop(philo);
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
