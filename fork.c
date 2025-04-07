#include "philo.h"

int	take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    printstatut(philo, "has taken a fork");

    pthread_mutex_lock(philo->right_fork);
    printstatut(philo, "has taken a fork");

    return (1);
}

int	eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = actual_time();
	pthread_mutex_unlock(&philo->meal_mutex);
    pthread_mutex_lock(&philo->meal_mutex);
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
    printstatut(philo, "has put down forks");
}