#include "philo.h"

void	printstatut(t_philo *philo, char *status)
{
    long int timestamp;

    pthread_mutex_lock(&philo->data->sim_mutex);
    timestamp = actual_time() - ((philo->data->start_time.tv_sec * 1000)
		+ (philo->data->start_time.tv_usec / 1000));
    if (!philo->data->simulation)
        printf("%ldms %d %s\n", timestamp, philo->id, status);
    pthread_mutex_unlock(&philo->data->sim_mutex);
}


int	main(int ac, char **av)
{
    t_data	data;
    t_philo	*philo;
    int		i;

    if (ac < 5 || ac > 6)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    parsing(av + 1);
    if (!init_value(av, &data) || !start_init_philo(&data, &philo))
        return (0);
    if (!init_mutex(&data, philo) || !fork_to_philo(&data, &philo))
        return (0);
    i = 0;
    monitoring(&data, philo);
    while (i < data.num_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    cleanup(&data, philo);
    return (0);
}