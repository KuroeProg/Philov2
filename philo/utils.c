/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiachet <cfiachet@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:13:30 by cfiachet          #+#    #+#             */
/*   Updated: 2025/04/09 15:27:39 by cfiachet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

long int	actual_time(void)
{
    struct timeval	current;

    if (gettimeofday(&current, NULL) == -1)
        return (-1);
    return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

void	ft_usleep(long int time)
{
	long int	start;

	start = 0;
	start = actual_time();
	while ((actual_time() - start) < time)
		usleep(time / 10);
}

void	cleanup(t_data *data, t_philo *philo)
{
    int i;

    if (data->fork)
    {
        i = 0;
        while (i < data->num_philo)
            pthread_mutex_destroy(&data->fork[i++]);
        free(data->fork);
    }
    if (philo)
    {
        i = 0;
        while (i < data->num_philo)
            pthread_mutex_destroy(&philo[i++].meal_mutex);
        free(philo);
    }
    pthread_mutex_destroy(&data->sim_mutex);
}
