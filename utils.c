/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <		   @student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:12:16 by cfiachet          #+#    #+#             */
/*   Updated: 2024/10/06 13:32:43 by cfiachet         ###   ########.fr       */
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

long int		actual_time(void)
{
	long int			time;
	struct timeval		current;

	time = 0;
	if (gettimeofday(&current, NULL) == -1)
		exit(1);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000); 
	return (time);
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