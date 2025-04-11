/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiachet <cfiachet@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:13:30 by cfiachet          #+#    #+#             */
/*   Updated: 2025/04/11 13:38:06 by cfiachet         ###   ########.fr       */
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

void	ft_usleep(long int time, t_philo *philo)
{
	long int	start;

	start = 0;
	start = actual_time();
	while ((actual_time() - start) < time)
	{
		pthread_mutex_lock(&philo->data->sim_mutex);
		if (philo->data->simulation)
		{
			pthread_mutex_unlock(&philo->data->sim_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->sim_mutex);
		usleep(1);
	}
}

void	cleanup(t_data *data, t_philo *philo)
{
	int	i;

	if (data->fork)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
		free(data->fork);
	}
	if (philo)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_destroy(&philo[i].meal_mutex);
			i++;
		}
		free(philo);
	}
	pthread_mutex_destroy(&data->sim_mutex);
}

void	cleanup_mutexes(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->sim_mutex);
}
