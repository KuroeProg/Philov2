/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiachet <cfiachet@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:26:06 by cfiachet          #+#    #+#             */
/*   Updated: 2025/04/09 20:36:38 by cfiachet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philo *philo, t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (philo[i].meals_eaten >= data->num_to_eat)
			count++;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	return (count == data->num_philo);
}

static int	check_philo_death(t_philo *philo, t_data *data)
{
    pthread_mutex_lock(&philo->meal_mutex);
    if ((actual_time() - philo->last_meal) > data->time_to_die)
    {
        printstatut(philo, "died");
        pthread_mutex_unlock(&philo->meal_mutex);
        pthread_mutex_lock(&data->sim_mutex);
        data->simulation = 1;
        pthread_mutex_unlock(&data->sim_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->meal_mutex);
    return (0);
}

static int	check_all_meals(t_philo *philo, t_data *data)
{
    if (data->num_to_eat > 0 && check_meals(philo, data))
    {
        pthread_mutex_lock(&data->sim_mutex);
        data->simulation = 1;
        pthread_mutex_unlock(&data->sim_mutex);
        return (1);
    }
    return (0);
}

void	*check_death(void *arg)
{
    t_data	*data = (t_data *)arg;
    t_philo	*philo = data->philos;
    int		i;

    while (data->simulation == 0)
    {
        i = 0;
        while (i < data->num_philo)
        {
            if (check_philo_death(&philo[i], data))
                return (NULL);
            i++;
        }
        if (check_all_meals(philo, data))
            return (NULL);
        ft_usleep(1);
    }
    return (NULL);
}

int	monitoring(t_data *data, t_philo *philo)
{
    pthread_t	death_thread;

	(void)philo;
    if (pthread_create(&death_thread, NULL, check_death, data) != 0)
        return (1);
    pthread_join(death_thread, NULL);
    return (data->simulation);
}
