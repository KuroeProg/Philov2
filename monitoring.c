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
	if (count == data->num_philo)
		return (1);
	return (0);
}


int	monitoring(t_data *data, t_philo *philo)
{
	int i = 0;

	while (data->simulation == 0)
	{
	    while (i < data->num_philo)
	    {
			if (data->simulation == 1)
				break ;
	        pthread_mutex_lock(&philo[i].meal_mutex);
	        if ((actual_time() - ((philo[i].last_meal.tv_sec * 1000)
				+ (philo[i].last_meal.tv_usec / 1000))) > data->time_to_die)
	        {
	            printstatut(&philo[i], "died");
	            pthread_mutex_unlock(&philo[i].meal_mutex);
	            pthread_mutex_lock(&data->sim_mutex);
	            data->simulation = 1;
	            pthread_mutex_unlock(&data->sim_mutex);
	            return (1);
	        }
	        pthread_mutex_unlock(&philo[i].meal_mutex);
	        i++;
	    }
	    if (data->num_to_eat > 0 && check_meals(philo, data))
	    {
	        pthread_mutex_lock(&data->sim_mutex);
	        data->simulation = 1;
	        pthread_mutex_unlock(&data->sim_mutex);
	        return (1);
	    }
	    i = 0;
	    ft_usleep(100);
	}
	return (0);
}
