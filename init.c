/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:50:49 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/08/10 01:04:03 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("less or more arguments\n");
		return (1);
	}
	i = 1;
	while (argv[i] != 0)
	{
		if (ft_isdigit(argv[i]) == 0 || ft_atoi(argv[i]) < 0)
		{
			printf("arguments is not vaild\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	malloc_data(char *argv[], t_data *data, t_philo **philo)
{
	*philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	data->death = (int *)malloc(sizeof(int));
	data->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(argv[1]));
	if (*philo == 0 || data->death == 0 || data->print == 0 || data->fork == 0)
	{
		free_data(data, *philo);
		printf("data malloc faild\n");
		return (1);
	}
	return (0);
}

void	init_data(char *argv[], t_data *data)
{
	int	i;

	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat_cnt = ft_atoi(argv[5]);
	else
		data->must_eat_cnt = -1;
	*(data->death) = 0;
	pthread_mutex_init(data->print, 0);
	pthread_mutex_init(data->eat, 0);
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_init(&data->fork[i], 0);
		i++;
	}
}

void	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].data = data;
		philo[i].num = i + 1;
		philo[i].eat_count = 0;
		philo[i].my_death = 0;
		philo[i].l_fork = &(data->fork[i]);
		if (i == data->num_of_philo - 1)
			philo[i].r_fork = &(data->fork[0]);
		else
			philo[i].r_fork = &(data->fork[i + 1]);
		i++;
	}
}

void	init_thread(t_data *data, t_philo *philo)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].last_eat = data->start_time;
		pthread_create(&(philo[i].thread), 0, &run_thread, &(philo[i]));
		pthread_create(&(philo[i].monitor), 0, &run_monitor, &(philo[i]));
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(philo[i].thread, 0);
		pthread_join(philo[i].monitor, 0);
		pthread_mutex_destroy(&(data->fork[i]));
		i++;
	}
	pthread_mutex_destroy(data->eat);
	pthread_mutex_destroy(data->print);
	free_data(data, philo);
}
