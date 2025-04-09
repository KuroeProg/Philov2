#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->data->num_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		printstatut(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		printstatut(philo, "died");
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->data->sim_mutex);
		philo->data->simulation = 1;
		pthread_mutex_unlock(&philo->data->sim_mutex);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	printstatut(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	printstatut(philo, "has taken a fork");
	return (1);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = actual_time();
	philo->meals_eaten++;
	printstatut(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	return (1);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}