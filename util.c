/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 22:44:54 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/09/27 22:45:25 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg(t_philo *philo, int flag)
{
	pthread_mutex_lock(philo->data->print);
	if (flag == FORK && *(philo->data->death) == 0)
		printf("%ld %d has taken a fork\n",
			get_time() - philo->data->start_time, philo->num);
	else if (flag == EAT && *(philo->data->death) == 0)
		printf("%ld %d is eating\n",
			get_time() - philo->data->start_time, philo->num);
	else if (flag == SLEEP && *(philo->data->death) == 0)
		printf("%ld %d is sleeping\n",
			get_time() - philo->data->start_time, philo->num);
	else if (flag == THINK && *(philo->data->death) == 0)
		printf("%ld %d is thinking\n",
			get_time() - philo->data->start_time, philo->num);
	else if (flag == DIE && *(philo->data->death) == 1 && philo->my_death == 1)
		printf("%ld %d died\n",
			get_time() - philo->data->start_time, philo->num);
	pthread_mutex_unlock(philo->data->print);
	if (*(philo->data->death) != 0)
		return (1);
	else
		return (0);
}

unsigned long	get_time(void)
{
	struct timeval	tmp;
	unsigned long	now;

	gettimeofday(&tmp, 0);
	now = tmp.tv_sec * 1000;
	now += tmp.tv_usec / 1000;
	return (now);
}

void	free_data(t_data *data, t_philo *philo)
{
	if (philo != 0)
		free(philo);
	if (data->death != 0)
		free(data->death);
	if (data->print != 0)
		free(data->print);
	if (data->fork != 0)
		free(data->fork);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	rst;
	int	pmsign;

	i = 0;
	rst = 0;
	pmsign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pmsign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rst = (rst * 10) + (str[i] - '0');
		i++;
	}
	if (i > 10)
		return (-1);
	return (rst * pmsign);
}

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
