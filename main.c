#include "philo.h"

void free_data(t_data *data, t_philo *philo)
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

int main(int argc, char *argv[])
{
    t_philo *philo;
    t_data data;
    
    if (check_input(argc, argv) != 0)
        return (0);
    if (malloc_data(argv, &data, &philo) != 0)
        return (0);
    init_data(argv, &data);
    init_philo(&data, philo);
    init_thread(&data, philo);
    return (0);
}