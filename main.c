/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:53:12 by jeonhyun          #+#    #+#             */
/*   Updated: 2021/08/06 17:28:42 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	t_data	data;

	if (check_input(argc, argv) != 0)
		return (0);
	if (malloc_data(argv, &data, &philo) != 0)
		return (0);
	init_data(argv, &data);
	init_philo(&data, philo);
	init_thread(&data, philo);
	return (0);
}
