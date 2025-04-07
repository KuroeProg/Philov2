#include "philo.h"

void	think(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->sim_mutex);
	printstatut(philo, "is thinking");
	// pthread_mutex_unlock(&philo->data->sim_mutex);
}

void	p_sleep(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->sim_mutex);
	printstatut(philo, "is sleeping");
	// pthread_mutex_unlock(&philo->data->sim_mutex);
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!philo->data->simulation)
	{
		think(philo);
		if (!take_forks(philo))
			break ;
		if (!eat(philo))
			break ;
		put_forks(philo);
		p_sleep(philo);
	}
	return (NULL);
}