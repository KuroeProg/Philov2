/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiachet <cfiachet@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:25:55 by cfiachet          #+#    #+#             */
/*   Updated: 2025/04/10 16:15:38 by cfiachet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printstatut(t_philo *philo, char *status)
{
	long int	timestamp;

	pthread_mutex_lock(&philo->data->sim_mutex);
	// pthread_mutex_lock(&philo->meal_mutex);
	timestamp = actual_time() - ((philo->data->start_time.tv_sec * 1000)
		+ (philo->data->start_time.tv_usec / 1000));
	if (!philo->data->simulation)
		printf("%ld %d %s\n", timestamp, philo->id, status);
	// pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->data->sim_mutex);
}


static int	init_simulation(int ac, char **av, t_data *data, t_philo **philo)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	parsing(av + 1);
	if (!init_value(av, data) || !start_init_philo(data, philo))
		return (0);
	data->philos = *philo;
	if (!init_mutex(data, *philo) || !fork_to_philo(data, philo))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	death_thread;
	int			i;

	if (!init_simulation(ac, av, &data, &philo))
		return (1);
	if (pthread_create(&death_thread, NULL, check_death, &data))
		return (cleanup(&data, philo), 1);
	i = 0;
	while (i < data.num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(death_thread, NULL);
	cleanup(&data, philo);
	return (0);
}