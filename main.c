#include "philo.h"

int main(int argc, char *argv[])
{
    t_philo *philo;
    t_data data;
    
    if (check_input(argc, argv) != 0)
		return (1);
	if (malloc_data(argv, &data, &philo) != 0)
		return (1);
	init_data(argv, &data);
	init_philo(&data, philo);
	init_thread(&data, philo);
    return (0);
}